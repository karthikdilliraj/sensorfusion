/**
 * Implementation of the main portion of the Fused Sensor Calculator.
 */

#include <stdio.h>
#include <stdlib.h>
#include "parsing_csv_file.h"
#include "linked_list.h"


#define INPUT_FILE_NAME "input.csv"


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
    float   sensor_value;
    char    sensor_name[MAX_SENSOR_NAME_SIZE];
    char    file_name[MAX_FILE_NAME_SIZE];
    int     time_in_minutes = 0;
    int     opt;
    float   low_range;
    float   high_range;
    int     use_high_range = 0;
    int     use_low_range = 0;
    int     lines_read = 1;
    int     end_of_file_reached = 0;
    int     current_time = -1;

    strncpy(file_name, INPUT_FILE_NAME, MAX_FILE_NAME_SIZE);
    while((opt = getopt(argc, argv, "tl:h:")) != -1)
    {
        /* TODO: Add -f file switch to specify file name */
        /* TODO: Add -s to specify stuck time */
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
                do_sensor_fusion_algorithm();
                current_time = -1;
            }
        }

        ++lines_read;
        if (test_mode)
        {
            printf("Read line %02d (Time: %d, Name: %s, Value: %0.2f)\n",
                   lines_read,
                   time_in_minutes,
                   sensor_name,
                   sensor_value);
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
               "Passing off to Sensor Fustion Calculation\n\n");
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


void run_test_suite(void)
{
    Node_t  *node = NULL;
    int     ch;
    char    str[MAX_SENSOR_NAME_SIZE];
    float   value;
    int     c;
    int     selection;
    int     i;
    int     selection_from;
    int     selection_to;

    while (1)
    {
        printf("\n 1 - Count list");
        printf("\n 2 - Insert at end");
        printf("\n 3 - Display from beginning");
        printf("\n 4 - Search for a Node");
        printf("\n 5 - Delete a Node");
        printf("\n 6 - Move a Node");
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
                scanf("%d", &selection_from);

                printf("Select list to move to:\n");
                scanf("%d", &selection_to);

                --selection_from;
                --selection_to;
                if (selection_from == selection_to)
                {
                    printf("Cannot move to and from same list\n");
                    break;
                }

                node
                    = search_sensor_name(sensor_list_head_array[selection_from],
                                         str);
                if (node)
                {
                    sensor_list_head_array[selection_to]
                        = append(sensor_list_head_array[selection_to],
                                 node->time_in_minutes,
                                 node->sensor_name,
                                 node->sensor_value);

                    sensor_list_head_array[selection_from]
                        = remove_node(sensor_list_head_array[selection_from],
                                      node);
                    break;
                }
                break;
            case 10:
                return;
            default:
                printf("\n Invalid option\n");
        }
    }
}
