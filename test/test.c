#include "test.h"

/**
 * Head pointers to three linked lists used for storing three types of sensors
 * retrieved from the specified input file.
 */
Node_t *test_list_head_array[MAX_SENSOR_LISTS] = {NULL};

/**
 * Macro to print out 'passed'/'failed' based on the boolean value of what was
 * provided to it.
 */
#define ASSERT_TEST(x)                        \
    {                                         \
        if (x)                                \
        {                                     \
            printf("PASSED\n");               \
        }                                     \
        else                                  \
        {                                     \
            printf("%s: FAILED\n", __func__); \
        }                                     \
    }

/**
 * Number of nodes to make for the purposes of testing.
 */
#define NUMBER_OF_TEST_NODES 6

/**
 * Name of the testing csv
 */
#define TEST_FILENAME "test/input_test.csv"

/**
 * Test values for the low and high range (sensor values outside of this range
 * will be put in the OOR list, instead of the valid list.
 */
#define TEST_LOW_RANGE 9
#define TEST_HIGH_RANGE 23

/**
 * Test value for the stuck range (sensor values that haven't been updated
 * within this range will be moved into the Stuck list, instead of the valid
 * list.
 */
#define TEST_STUCK_RANGE 20

void automated_testing_linked_list(void)
{
    Boolean rc;
    Node_t *node = NULL;
    float value;
    char test[10] = "test";
    char str[10];
    int num_nodes = NUMBER_OF_TEST_NODES;
    int time;
    int i;

    printf("-------------------\n");
    printf("LINKED LIST TESTING\n");
    printf("-------------------\n");
    /**
     * Add new nodes to a linked list. We will add six nodes and make
     * sure they are present.
     */
    time = 10;
    for (i = 1; i <= NUMBER_OF_TEST_NODES; i++)
    {
        sprintf(str, "%s%d", test, i);
        value = i * 10;
        printf("Adding node - Name: %s, Time: %d, Value: %0.2f - ",
               str,
               time,
               value);

        test_list_head_array[VALID_SENSOR_LIST] =
            update(test_list_head_array[VALID_SENSOR_LIST],
                   time,
                   str,
                   value);
        node = search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                                  str);
        ASSERT_TEST(node &&
                    (strcmp(node->sensor_name, str) == 0) &&
                    (node->sensor_value == value) &&
                    (node->time_in_minutes == time))
    }
    printf("Ensure %d nodes exist in list 1 - ", NUMBER_OF_TEST_NODES);
    ASSERT_TEST(count(test_list_head_array[VALID_SENSOR_LIST]) ==
                NUMBER_OF_TEST_NODES)
    printf("\n");

    /**
     * Update existing nodes in a linked list. We will make sure they all have
     * the updated value, and that there are still six nodes (ie: Nothing got
     * added instead).
     */
    time = 13;
    for (i = 1; i <= NUMBER_OF_TEST_NODES; i++)
    {
        sprintf(str, "%s%d", test, i);
        value = i * 11;
        printf("Updating node - Name: %s, Time: %d, Value: %0.2f - ",
               str,
               time,
               value);

        test_list_head_array[VALID_SENSOR_LIST] =
            update(test_list_head_array[VALID_SENSOR_LIST],
                   time,
                   str,
                   value);
        node = search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                                  str);
        ASSERT_TEST(node &&
                    (strcmp(node->sensor_name, str) == 0) &&
                    (node->sensor_value == value) &&
                    (node->time_in_minutes == time))
    }
    printf("Ensure %d nodes exist in list 1 - ", NUMBER_OF_TEST_NODES);
    ASSERT_TEST(count(test_list_head_array[VALID_SENSOR_LIST]) ==
                NUMBER_OF_TEST_NODES)

    /**
     * Move node from one list to another list. We will check to make sure
     * that the original list has 5 members, and the new list has one.
     */
    printf("\nMove node from list 1 to list 2 - ");
    node = search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                              "test3");
    rc = move_node(&test_list_head_array[VALID_SENSOR_LIST],
                   &test_list_head_array[OOR_SENSOR_LIST], node);
    ASSERT_TEST(rc &&
                (search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                                    "test3") == NULL) &&
                (search_sensor_name(test_list_head_array[OOR_SENSOR_LIST],
                                    "test3") != NULL))

    /**
     * Delete node from list 2 and ensure list 2 is now empty
     */
    printf("Delete only node from list 2 ---- ");
    test_list_head_array[OOR_SENSOR_LIST] =
        remove_node(test_list_head_array[OOR_SENSOR_LIST],
                    node);
    ASSERT_TEST(search_sensor_name(test_list_head_array[OOR_SENSOR_LIST],
                                   "test3") == NULL)
    --num_nodes;

    printf("Ensure 0 nodes in list 2 -------- ");
    ASSERT_TEST(count(test_list_head_array[OOR_SENSOR_LIST]) == 0)

    /**
     * Delete node from middle of list 1 and make sure that it is gone. Also
     * ensure that there are four nodes in the list.
     */
    strcpy(str, "test4");
    printf("\nDelete from middle of list 1 - ");
    node = search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                              str);

    test_list_head_array[VALID_SENSOR_LIST] =
        remove_node(test_list_head_array[VALID_SENSOR_LIST],
                    node);
    ASSERT_TEST(search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                                   str) == NULL)
    --num_nodes;
    printf("Ensure %d nodes in list 1 ----- ", num_nodes);
    ASSERT_TEST(count(test_list_head_array[VALID_SENSOR_LIST]) == num_nodes)

    /**
     * Delete node from end of list 1 and make sure that it is gone. Also
     * ensure that there are three nodes in the list.
     */
    strcpy(str, "test6");
    printf("\nDelete from end of list 1 - ");
    node = search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                              str);

    test_list_head_array[VALID_SENSOR_LIST] =
        remove_node(test_list_head_array[VALID_SENSOR_LIST],
                    node);
    ASSERT_TEST(search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                                   str) == NULL)
    --num_nodes;
    printf("Ensure %d nodes in list 1 -- ", num_nodes);
    ASSERT_TEST(count(test_list_head_array[VALID_SENSOR_LIST]) == num_nodes)

    /**
     * Delete node from beginning of list 1 and make sure that it is gone. Also
     * ensure that there are two nodes in the list.
     */
    strcpy(str, "test1");
    printf("\nDelete from end of list 1 - ");
    node = search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                              str);

    test_list_head_array[VALID_SENSOR_LIST] =
        remove_node(test_list_head_array[VALID_SENSOR_LIST],
                    node);
    ASSERT_TEST(search_sensor_name(test_list_head_array[VALID_SENSOR_LIST],
                                   str) == NULL)
    --num_nodes;
    printf("Ensure %d nodes in list 1 -- ", num_nodes);
    ASSERT_TEST(count(test_list_head_array[VALID_SENSOR_LIST]) == num_nodes)

    /**
     * Delete the rest of the nodes from the beginning of the list. We want to
     * clean up here so everything is empty for later.
     */
    while (count(test_list_head_array[VALID_SENSOR_LIST]) > 0)
    {
        printf("\nDelete from beginning of list 1\n");
        test_list_head_array[VALID_SENSOR_LIST] =
            remove_from_front(test_list_head_array[VALID_SENSOR_LIST]);
        --num_nodes;
        printf("Ensure %d nodes in list 1 - ", num_nodes);
        ASSERT_TEST(count(test_list_head_array[VALID_SENSOR_LIST]) == num_nodes)
    }
}

void automated_testing_csv_parsing(void)
{
    Boolean end_of_file_reached = FALSE;
    float sensor_value;
    float test_sensor_value;
    char sensor_name[MAX_SENSOR_NAME_SIZE];
    char test_sensor_name[MAX_SENSOR_NAME_SIZE];
    int time_in_minutes;
    int lines_read = 1;
    int test_time_in_minutes;

    printf("\n\n");
    printf("-------------------\n");
    printf("PARSER TESTING\n");
    printf("-------------------\n");

    do
    {
        end_of_file_reached = parser_parse_csv_file(TEST_FILENAME,
                                                    lines_read,
                                                    &time_in_minutes,
                                                    &sensor_name[0],
                                                    &sensor_value);

        switch (lines_read)
        {
        case 1:
            test_time_in_minutes = 540;
            strcpy(test_sensor_name, "sens1");
            test_sensor_value = 10;
            break;
        case 2:
            test_time_in_minutes = 540;
            strcpy(test_sensor_name, "sens2");
            test_sensor_value = 12;
            break;
        case 3:
            test_time_in_minutes = 570;
            strcpy(test_sensor_name, "sens3");
            test_sensor_value = 14;
            break;
        case 4:
            test_time_in_minutes = 570;
            strcpy(test_sensor_name, "sens2");
            test_sensor_value = 13;
            break;
        default:
            return;
        }

        printf("First line should read: %d.%02d,%s,%0.0f - ",
               test_time_in_minutes / 60,
               test_time_in_minutes % 60,
               test_sensor_name,
               test_sensor_value);
        ASSERT_TEST((time_in_minutes == test_time_in_minutes) &&
                    (strcmp(test_sensor_name, sensor_name) == 0) &&
                    test_sensor_value == sensor_value)

        ++lines_read;
    } while (!end_of_file_reached);
}

void automated_sensor_manipulation(void)
{
    Boolean end_of_file_reached = FALSE;
    Node_t *node;
    float sensor_value;
    char sensor_name[MAX_SENSOR_NAME_SIZE];
    char test_name[MAX_SENSOR_NAME_SIZE];
    int time_in_minutes;
    int lines_read = 1;
    int list_index;

    printf("\n\n");
    printf("-------------------\n");
    printf("SENSOR TESTING\n");
    printf("-------------------\n");

    do
    {
        end_of_file_reached = parser_parse_csv_file(TEST_FILENAME,
                                                    lines_read,
                                                    &time_in_minutes,
                                                    &sensor_name[0],
                                                    &sensor_value);

        update_sensor_lists(time_in_minutes,
                            sensor_name,
                            sensor_value,
                            TRUE,
                            TEST_HIGH_RANGE,
                            TRUE,
                            TEST_LOW_RANGE);

        determine_if_sensors_are_stuck(time_in_minutes, TEST_STUCK_RANGE);

        ++lines_read;

    } while (!end_of_file_reached);

    strcpy(test_name, "sens1");
    printf("Ensure node \'%s\' is in Valid list - ", test_name);
    node = search_all_chains(test_name, &list_index);
    ASSERT_TEST(node && (list_index == VALID_SENSOR_LIST))

    strcpy(test_name, "sens2");
    printf("Ensure node \'%s\' is in Stuck list - ", test_name);
    node = search_all_chains(test_name, &list_index);
    ASSERT_TEST(node && (list_index == STUCK_SENSOR_LIST))

    strcpy(test_name, "sens3");
    printf("Ensure node \'%s\' is in OOR list --- ", test_name);
    node = search_all_chains(test_name, &list_index);
    ASSERT_TEST(node && (list_index == OOR_SENSOR_LIST))

    strcpy(test_name, "sens4");
    printf("Ensure node \'%s\' is in Stuck list - ", test_name);
    node = search_all_chains(test_name, &list_index);
    ASSERT_TEST(node && (list_index == STUCK_SENSOR_LIST))

    strcpy(test_name, "sens5");
    printf("Ensure node \'%s\' is in OOR list --- ", test_name);
    node = search_all_chains(test_name, &list_index);
    ASSERT_TEST(node && (list_index == OOR_SENSOR_LIST))
}

void automated_calculate_support_degree_matrix(void)
{
    struct support_degree_matrix spd_test = calculate_support_degree_matrix();
    ASSERT_TEST(spd_test.no_of_sensors != 0 && spd_test.sd_matrix != NULL )
    free(spd_test);
    spd_test = NULL;
}

void automated_calculate_eigensystem(void)
{
    struct support_degree_matrix spd_test;
    spd_test.no_of_sensors = 2;
    spd_test.sd_matrix = {1.0,0.000045,0.000045,1.0};
    struct eigen_systems eigen_test = calculate_eigensystem(spd_test);
    ASSERT_TEST(eigen_test.eigen_value != NULL && eigen_test.eigen_vector != NULL )
    free(spd_test);
    spd_test = NULL;
    free(eigen_test);
    eigen_test = NULL;
}

void automated_calculate_contribution_rate(void)
{
    struct eigen_systems eigen_test;
    eigen_test.eigen_value = {1.00005, 0.999955};
    eigen_test.eigen_vector = {{0.707107,0.707107},{-0.707107,0.707107}};
    int n=2;
    double *contribution_rate = calculate_contribution_rates(eigen_test,n);
    ASSERT_TEST(contribution_rate != NULL)
    free(eigen_test);
    eigen_test = NULL;
    free(contribution_rate);
}

void automated_determine_contribution_rates_to_use(void)
{
    double *contribution_rate = {0.500023,0.499977}
    int no_of_sensors = 2;
    int to_use = determine_contribution_rates_to_use(contribution_rate, no_of_sensors);
    ASSERT_TEST(to_use != 0)
    free(contribution_rate);
}

void automated_calculate_principal_components(void)
{
    struct support_degree_matrix spd_test;
    spd_test.no_of_sensors = 2;
    spd_test.sd_matrix = {1.0,0.000045,0.000045,1.0}; 
    double **eigen_vector = {{0.707107,0.707107},{-0.707107,0.707107}};
    int to_use = 2;
    double ** principal_components_matrix = calculate_principal_components(spd_test,eigen_vector,to_use);
    ASSERT_TEST(principal_components_matrix != NULL)
    free(spd_test);
    spd_test = NULL;
    free(eigen_vector);
    free(principal_components_matrix);
}

void start_automated_testing(void)
{
    automated_testing_linked_list();
    automated_testing_csv_parsing();
    automated_sensor_manipulation();
    automated_calculate_support_degree_matrix();
    automated_calculate_eigensystem();
    automated_calculate_contribution_rate();
    automated_determine_contribution_rates_to_use();
    automated_calculate_principal_components();
}
