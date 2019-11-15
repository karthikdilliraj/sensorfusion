/**
 * Implementation of the main portion of the Fused Sensor Calculator.
 */

#include <stdio.h>
#include <stdlib.h>
#include "parsing_csv_file.h"
#include "linked_list.h"
#include "eigensystems.h"
#include "calculate_fusion.h"

/**
 * Currently, the exe gets put into sensorfusion/bin directory, but the input
 * file is in sensorfusion/src, so we will go down one directory, and up into
 * src to find the file.
 */
#define INPUT_FILE_NAME "../src/input.csv"


/**
 * The sensor lists are split into three:
 *  Valid sensors
 *  Out of range sensor
 *  Stuck sensors
 */
#define MAX_SENSOR_LISTS    3
#define VALID_SENSOR_LIST   0
#define OOR_SENSOR_LIST     1
#define STUCK_SENSOR_LIST   2


/* Test mode activated by -t switch. */
static int test_mode = 0;


/**
 * Head pointers to three linked lists used for storing three types of sensors
 * retrieved from the specified input file.
 */
Node_t  *sensor_list_head_array[MAX_SENSOR_LISTS] = {NULL};


/**
 * Function:    do_sensor_fusion_algorithm
 *
 * Parameters:
 *  None
 *
 * Entry point to the Fused Sensor Algorithm
 *
 * Return:
 *  Nothing.
 */
void do_sensor_fusion_algorithm(void);


/**
 * Function:    move_node_between_chains
 *
 * Parameters:
 *  sel_from    [in]    Index of the chain to move from
 *  sel_to      [in]    Index of the chain to move to
 *  *node       [in]    Node to move between chains
 *
 * Removes *node from the linked list pointed to by
 * *sensor_list_head_array[sel_from] and adds it to the linked list pointed to
 * by *sensor_list_head_array[sel_to]
 *
 * Return:
 *  Nothing.
 */
void move_node_between_chains(int sel_from, int sel_to, Node_t *node);


/**
 * Function:    search_all_chains
 *
 * Parameters:
 *  *str        [in]    Sensor name to search for
 *  *list_index [out]   Index of the chain that str was found in.
 *
 * Searches all linked list chains for a node containing a sensor name of *str.
 * If found, will put the list index in which the node was found into
 * *list_index and return a valid Node_t object.
 *
 * Return:
 *  Pointer to the matching node, if no node is found, returns NULL.
 */
Node_t* search_all_chains(char *str, int *list_index);


/**
 * Function:    determine_if_sensors_are_stuck
 *
 * Parameters:
 *  current_time    [in]    The current time with respect to where the parser
 *                          is within the input.csv file.
 *  stuck_value     [in]    User specified limit for determining stuck sensors.
 *
 * Iterates through the valid sensor list and the out of range sensor list to
 * see if any sensors have not been updated within an interval of stuck_value.
 * If so, will move that node from its current list into the stuck sensor list.
 *
 * Return:
 *  Nothing.
 */
void determine_if_sensors_are_stuck(int current_time, int stuck_value);


/**
 * Function:    dump_current_lists
 *
 * Parameters:
 *  Nothing
 *
 * A compact dump of all the nodes contained within all the linked lists.
 *
 * Return:
 *  Nothing.
 */
void dump_current_lists(void);


/**
 * Function:    run_test_suite
 *
 * Parameters:
 *  None
 *
 * Allows user to run debugging commands on the linked list after its parsed
 * from the CSV.
 *
 * Return:
 *  Nothing.
 */
void run_test_suite(void);


int main(int argc, char *argv[])
{
    Node_t  *node = NULL;
    float   sensor_value;
    char    sensor_name[MAX_SENSOR_NAME_SIZE];
    char    file_name[MAX_FILE_NAME_SIZE];
    int     time_in_minutes = 0;
    int     opt;
    float   high_range;
    float   low_range;
    int     end_of_file_reached = 0;
    int     use_high_range = 0;
    int     use_low_range = 0;
    int     current_time = -1;
    int     stuck_range;
    int     list_index;
    int     lines_read = 1;
    int     use_stuck = 0;

    /**
     * Run testing for calculate_fusion.c
     */
    double *support_degree_matrix = calculate_support_degree_matrix();
    calculate_eigensystem(support_degree_matrix);

    strncpy(file_name, INPUT_FILE_NAME, MAX_FILE_NAME_SIZE);
    while((opt = getopt(argc, argv, "tl:h:s:f:")) != -1)
    {
        switch(opt)
        {
            case 't':
                /* Activate the testing mode */
                printf("Testing mode activated\n");
                test_mode = 1;
                break;
            case 'l':
                /**
                 * Specifies the low edge of the valid sensor range. If the
                 * sensor value is below this, it goes into the out of range
                 * sensor list.
                 */
                low_range = strtod(optarg, NULL);
                use_low_range = 1;
                break;
            case 'h':
                /**
                 * Specifies the high edge of the valid sensor range. If the
                 * sensor value is above this, it goes into the out of range
                 * sensor list.
                 */
                high_range = strtod(optarg, NULL);
                use_high_range = 1;
                break;
            case 's':
                /**
                 * Specifies how long (in minutes) beyond which, the sensor is
                 * considered to be stuck, and no longer valid.
                 */
                stuck_range = strtod(optarg, NULL);
                use_stuck = 1;
                break;
            case 'f':
                /**
                 * Specifies a non-default input file to use for the sensor
                 * input data.
                 */
                strncpy(file_name, optarg, MAX_FILE_NAME_SIZE);
                break;
            default:
                printf("unknown option: %c\n", opt);
                break;
        }
    }

    do
    {
        end_of_file_reached = parser_parse_csv_file(file_name,
                                                    lines_read,
                                                    &time_in_minutes,
                                                    &sensor_name[0],
                                                    &sensor_value);
        if (current_time == -1)
        {
            /**
             * This is the first time that we are looking at, we want to get
             * other sensors that have updated at the same time as well.
             */
            current_time = time_in_minutes;
        }
        else
        {
            /**
             * We want to check to see that the value we have just read was
             * updated at the same time as all the other values we have
             * collected.
             */
            if (time_in_minutes != current_time)
            {
                /**
                 * We have read a line that has a different time stamp than
                 * the rest (or we have hit the end of the file)
                 */
                if (use_stuck)
                {
                    determine_if_sensors_are_stuck(current_time,
                                                   stuck_range);
                }

                if (test_mode)
                {
                    dump_current_lists();
                }

                do_sensor_fusion_algorithm();
                current_time = -1;
            }
        }

        ++lines_read;

        /**
         * Check to see if the node already exists. If it does, we will remove
         * it from the chain it belongs to, it will be re-added in a bit.
         */
        node = search_all_chains(sensor_name, &list_index);
        if (node)
        {
            sensor_list_head_array[list_index]
                = remove_node(sensor_list_head_array[list_index],
                              node);
        }

        if ((use_high_range) && (sensor_value > high_range))
        {
            /**
             * Sensor is above the high range, so we dump it into the out of
             * range list.
             */
            sensor_list_head_array[OOR_SENSOR_LIST]
                = append(sensor_list_head_array[OOR_SENSOR_LIST],
                         time_in_minutes,
                         sensor_name,
                         sensor_value);
        }
        else if ((use_low_range) && (sensor_value < low_range))
        {
            /**
             * Sensor is below the low range, so we dump it into the out of
             * range list.
             */
            sensor_list_head_array[OOR_SENSOR_LIST]
                = append(sensor_list_head_array[OOR_SENSOR_LIST],
                         time_in_minutes,
                         sensor_name,
                         sensor_value);
        }
        else
        {
            /* Sensor is fine, it gets to go into the valid list. */
            sensor_list_head_array[VALID_SENSOR_LIST]
                = append(sensor_list_head_array[VALID_SENSOR_LIST],
                         time_in_minutes,
                         sensor_name,
                         sensor_value);
        }
    } while (!end_of_file_reached);

    /**
     * Hitting the end of the file is not the same as finding all the entries
     * with the same timestamp, so we will run the fusion algorithm after
     * hitting the end of the file since there will be no more entries.
     */
    if (use_stuck)
    {
        determine_if_sensors_are_stuck(time_in_minutes, stuck_range);
    }

    if (test_mode)
    {
        dump_current_lists();
    }

    do_sensor_fusion_algorithm();

    if (test_mode)
    {
        run_test_suite();
    }

    return 0;
}


void do_sensor_fusion_algorithm(void)
{
    if (test_mode)
    {
        printf("Found all the values from the same time. "
               "Passing off to Sensor Fusion Calculation\n\n");
    }

    /**
     * Call step one of the Fused Sensor Calculation here with a
     * pointer to the head of the valid_sensor_list
     *
     * c = count(sensor_list_head_array[VALID_SENSOR_LIST]);
     * calculate_support_degree_matrix(c,
     *    sensor_list_head_array[VALID_SENSOR_LIST]);
     */
}


void move_node_between_chains(int sel_from, int sel_to, Node_t *node)
{
    if (node)
    {
        sensor_list_head_array[sel_to] = append(sensor_list_head_array[sel_to],
                                                node->time_in_minutes,
                                                node->sensor_name,
                                                node->sensor_value);

        sensor_list_head_array[sel_from]
            = remove_node(sensor_list_head_array[sel_from],
                          node);
    }
}


Node_t* search_all_chains(char *str, int *list_index)
{
    Node_t  *node = NULL;
    int     i;

    for (i = 0; i < MAX_SENSOR_LISTS; i++)
    {
        node = search_sensor_name(sensor_list_head_array[i], str);
        if (node)
        {
            (*list_index) = i;
            return node;
        }
    }

    return NULL;
}


void determine_if_sensors_are_stuck(int current_time, int stuck_value)
{
    Node_t  *node = NULL;
    Node_t  *next = NULL;
    int     i;

    for (i = 0; i < MAX_SENSOR_LISTS; i++)
    {
        if (i == STUCK_SENSOR_LIST)
        {
            /**
             * We don't need to check the stuck sensor list. They're already
             * stuck.
             */
            continue;
        }

        node = sensor_list_head_array[i];
        while (node)
        {
            /**
             * We're moving around nodes here, so we want to make sure we're
             * pointing to the correct next node, before we do any sort of
             * manipulation.
             */
            next = node->next;
            if ((node->time_in_minutes + stuck_value) < current_time)
            {
                /**
                 * Sensor has not been updated recently enough and must be
                 * considered stuck. It will be moved to the stuck list.
                 */
                move_node_between_chains(i, STUCK_SENSOR_LIST, node);
            }

            node = next;
        }
    }
}


void dump_current_lists(void)
{
    Node_t  *node = NULL;
    int     i;

    for (i = 0; i < MAX_SENSOR_LISTS; i++)
    {
        node = sensor_list_head_array[i];
        while (node)
        {
            switch (i)
            {
                case VALID_SENSOR_LIST:
                    printf("Valid - ");
                    break;

                case OOR_SENSOR_LIST:
                    printf("  OOR - ");
                    break;

                case STUCK_SENSOR_LIST:
                    printf("Stuck - ");
                    break;

                default:
                    printf("Invalid list\n");
                    return;
                    break;
            }

            printf("Time: %d, Value: %f, Name: %s\n",
                   node->time_in_minutes,
                   node->sensor_value,
                   node->sensor_name);
            node = node->next;
        }
    }
}


void run_test_suite(void)
{
    Node_t  *node = NULL;
    int     ch;
    char    str[MAX_SENSOR_NAME_SIZE];
    float   value;
    int     c;
    int     selection;
    int     i;
    int     sel_from;
    int     sel_to;

    while (1)
    {
        printf("\n 1 - Count list");
        printf("\n 2 - Insert at end");
        printf("\n 3 - Display from beginning");
        printf("\n 4 - Search for a Node");
        printf("\n 5 - Delete a Node");
        printf("\n 6 - Move a Node");
        printf("\n 7 - Update a Node");
        printf("\n 10 - Exit");

        selection = 0;
        printf("\n Enter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                printf("Select list:\n"
                       "  1 - Valid Sensor List\n"
                       "  2 - Out of Range Sensor List\n"
                       "  3 - Stuck Sensor List\n");
                scanf("%d", &selection);

                --selection;
                if (selection < MAX_SENSOR_LISTS)
                {
                    c = count(sensor_list_head_array[selection]);
                    printf("There are %d elements in this list\n", c);
                }
                break;
            case 2:
                printf("\n Enter time (in minutes): ");
                scanf("%d", &ch);
                printf("\n Enter sensor name: ");
                scanf("%s", &str[0]);
                printf("\n Enter sensor value: ");
                scanf("%f", &value);

                printf("Select list:\n"
                       "  1 - Valid Sensor List\n"
                       "  2 - Out of Range Sensor List\n"
                       "  3 - Stuck Sensor List\n");
                scanf("%d", &selection);
                --selection;
                if (selection < MAX_SENSOR_LISTS)
                {
                    sensor_list_head_array[selection]
                        = append(sensor_list_head_array[selection],
                                 ch,
                                 str,
                                 value);
                }
                break;
            case 3:
                printf("Select list:\n"
                       "  1 - Valid Sensor List\n"
                       "  2 - Out of Range Sensor List\n"
                       "  3 - Stuck Sensor List\n");
                scanf("%d", &selection);
                --selection;
                if (selection < MAX_SENSOR_LISTS)
                {
                    display(sensor_list_head_array[selection]);
                }
                break;
            case 4:
                printf("\n Enter sensor name to search: ");
                scanf("%s", &str[0]);

                for (i = 0; i < MAX_SENSOR_LISTS; i++)
                {
                    node = search_sensor_name(sensor_list_head_array[i], str);
                    if (node)
                    {
                        printf("Node found\n");
                        display_node(node);
                    }
                }
                break;
            case 5:
                printf("\n Enter sensor name to delete: ");
                scanf("%s", &str[0]);

                for (i = 0; i < MAX_SENSOR_LISTS; i++)
                {
                    node = search_sensor_name(sensor_list_head_array[i], str);
                    if (node)
                    {
                        sensor_list_head_array[i]
                            = remove_node(sensor_list_head_array[i], node);
                        display(sensor_list_head_array[i]);
                        break;
                    }
                }
                break;
            case 6:
                printf("\n Enter sensor name to move: ");
                scanf("%s", &str[0]);

                printf("Select list to move from:\n"
                       "  1 - Valid Sensor List\n"
                       "  2 - Out of Range Sensor List\n"
                       "  3 - Stuck Sensor List\n");
                scanf("%d", &sel_from);

                printf("Select list to move to:\n");
                scanf("%d", &sel_to);

                --sel_from;
                --sel_to;
                if (sel_from == sel_to)
                {
                    printf("Cannot move to and from same list\n");
                    break;
                }

                node = search_sensor_name(sensor_list_head_array[sel_from],
                                          str);
                if (node)
                {
                    move_node_between_chains(sel_from, sel_to, node);
                }
                break;
            case 7:
                printf("\n Enter sensor name to update: ");
                scanf("%s", &str[0]);

                printf("\n Enter time (in minutes): ");
                scanf("%d", &ch);
                printf("\n Enter sensor value: ");
                scanf("%f", &value);

                for (i = 0; i < MAX_SENSOR_LISTS; i++)
                {
                    node = search_sensor_name(sensor_list_head_array[i], str);
                    if (node)
                    {
                        sensor_list_head_array[i]
                            = update(sensor_list_head_array[i], ch, str, value);
                        display(sensor_list_head_array[i]);
                        break;
                    }
                }
                break;
            case 10:
                return;
            default:
                printf("\n Invalid option\n");
        }
    }
}
