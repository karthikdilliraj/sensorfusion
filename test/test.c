#include "test.h"
#include <math.h>

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
    rc = move_node(node,
                   &test_list_head_array[VALID_SENSOR_LIST],
                   &test_list_head_array[OOR_SENSOR_LIST]);
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
#if 0
    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE SUPPORT DEGREE MATRIX TESTING\n");
    printf("-------------------\n");

    double expected_sd_matrix[] = {1.0,
                                   0.000045,
                                   0.000045,
                                   1.0};

    struct support_degree_matrix *spd_test = calculate_support_degree_matrix();
    int n = spd_test->no_of_sensors;
    if (n < 1)
    {
        printf("Unable to call calculate_fused_output\n");
        ASSERT_TEST(spd_test->no_of_sensors == 0);
    }
    printf("Ensure correctness of elminination ---\n");
    for (int i = 0; i < n * n; i++)
    {
        if (spd_test->sd_matrix[i] != expected_sd_matrix[i])
        {
            ASSERT_TEST(spd_test->sd_matrix[i] == expected_sd_matrix[i]);
            printf("Expected:%f --- Calculated:%f\n", expected_sd_matrix[i], spd_test->sd_matrix[i]);
            free(spd_test->sd_matrix);
            free(spd_test);
            return;
        }
    }
    free(spd_test->sd_matrix);
    free(spd_test);
    printf("PASSED!\n");
#endif
}

void automated_calculate_eigensystem(void)
{
    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE EIGENSYSTEM TESTING\n");
    printf("-------------------\n");

    double expected_eigen_vector[][2] = {{0.707107, 0.707107}, {-0.707107, 0.707107}};
    double expected_eigen_value[] = {11.0, -9.0};
    int no_of_sensors = 2;
    double sd_matrix[] = {1.0, 10.0, 10.0, 1.0};
    struct eigen_systems *eigen_test = calculate_eigensystem(sd_matrix, no_of_sensors);
    printf("Ensure correctness of calculation ---\n");
    for (int i = 0; i < 2; i++)
    {
        double result_diff = fabs(eigen_test->eigen_value[i] - expected_eigen_value[i]);
        if (result_diff > EPSILON)
        {
            ASSERT_TEST(eigen_test->eigen_value[i] == expected_eigen_value[i]);
            printf("Expected:%f --- Calculated:%f\n", expected_eigen_value[i], eigen_test->eigen_value[i]);
            free(eigen_test->eigen_value);
            free(eigen_test->eigen_vector);
            free(eigen_test);
            return;
        }
        for (int j = 0; j < 2; j++)
        {
            double result_diff = fabs(eigen_test->eigen_vector[i][j] - expected_eigen_vector[i][j]);
            if (result_diff > EPSILON)
            {
                ASSERT_TEST(eigen_test->eigen_vector[i][j] == expected_eigen_vector[i][j]);
                printf("Expected:%f --- Calculated:%f\n", expected_eigen_vector[i][j], eigen_test->eigen_vector[i][j]);
                free(eigen_test->eigen_value);
                free(eigen_test->eigen_vector);
                free(eigen_test);
                return;
            }
        }
    }
    free(eigen_test->eigen_value);
    free(eigen_test->eigen_vector);
    free(eigen_test);
    printf("PASSED!\n");
}

void automated_calculate_contribution_rate(void)
{
    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE CONTRIBUTION RATE TESTING\n");
    printf("-------------------\n");
    double expected_contribution_rate[] = {0.500023, 0.499977};
    double eigen_value[] = {1.00005,
                            0.999955};
    int no_of_sensors = 2;
    double *calculated_contribution_rate = calculate_contribution_rate(eigen_value, no_of_sensors);
    printf("Ensure correctness of calculation ---\n");
    for (int i = 0; i < 2; i++)
    {
        double result_diff = fabs(calculated_contribution_rate[i] - expected_contribution_rate[i]);
        if (result_diff > EPSILON)
        {
            ASSERT_TEST(calculated_contribution_rate[i] == expected_contribution_rate[i]);
            printf("Expected:%f --- Calculated:%f\n", expected_contribution_rate[i], calculated_contribution_rate[i]);
            free(calculated_contribution_rate);
            return;
        }
    }
    free(calculated_contribution_rate);
    printf("PASSED!\n");
}

void automated_determine_contribution_rates_to_use(void)
{
    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE NUMBER OF CONTRIBUTION RATES TO USE TESTING\n");
    printf("-------------------\n");
    int expected_contribution_rates_to_use = 2;
    double contribution_rate[] = {0.500023,
                                  0.499977};
    int no_of_sensors = 2;
    float parameter = 0.5;
    int determined_contribution_rates_to_use = determine_contribution_rates_to_use(contribution_rate, parameter, no_of_sensors);
    printf("Ensure correctness of calculation ---\n");
    if (determined_contribution_rates_to_use != expected_contribution_rates_to_use)
    {
        ASSERT_TEST(determined_contribution_rates_to_use == expected_contribution_rates_to_use);
        printf("Expected:%d --- Calculated:%d\n", expected_contribution_rates_to_use, determined_contribution_rates_to_use);
    }
    printf("PASSED!\n");
}

void automated_calculate_principal_components(void)
{
    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE PRINCIPAL COMPONENTS TESTING\n");
    printf("-------------------\n");
    double expected_principal_components_matrix[][2] = {{0.707139, 0.707139},
                                                        {-0.707075, 0.707075}};
    double sd_matrix[] = {1.0, 0.000045, 0.000045, 1.0};
    int no_of_sensors = 2;
    double **eigen_vector = (double **)malloc(2 * sizeof(double *));
    for (int i = 0; i < 2; i++)
    {
        eigen_vector[i] = (double *)malloc(2 * sizeof(double));
    }
    eigen_vector[0][0] = 0.707107;
    eigen_vector[0][1] = 0.707107;
    eigen_vector[1][0] = -0.707107;
    eigen_vector[1][1] = 0.707107;
    int contribution_rates_to_use = 2;
    double **calculated_principal_components_matrix = calculate_principal_components(sd_matrix, no_of_sensors, eigen_vector, contribution_rates_to_use);
    printf("Ensure correctness of calculation ---\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            double result_diff = fabs(calculated_principal_components_matrix[i][j] - expected_principal_components_matrix[i][j]);
            if (result_diff > EPSILON)
            {
                ASSERT_TEST(calculated_principal_components_matrix[i][j] == expected_principal_components_matrix[i][j]);
                printf("Expected:%f --- Calculated:%f\n", expected_principal_components_matrix[i][j], calculated_principal_components_matrix[i][j]);
                free(eigen_vector);
                free(calculated_principal_components_matrix);
                return;
            }
        }
    }
    free(eigen_vector);
    free(calculated_principal_components_matrix);
    printf("PASSED!\n");
}

void automated_calculate_integrated_support_degree_matrix(void)
{
    double contribution_rate_test[] = {0.1, 0.2, 0.3, 0.4};
    double n_sensor_t = 4;
    double n_contri_rate_t = 3;
    double **principal_components_matrix_test =
        (double **)malloc(n_sensor_t * sizeof(double *));
    int i;
    int j;

    double expected_support_matrix[3] = {1.4, 1.4, 1.4};
    double *calculated_support_matrix;

    if (!principal_components_matrix_test)
    {
        printf("Error running test case (malloc failed)\n");
        return;
    }

    for (i = 0; i < n_sensor_t; i++)
    {
        principal_components_matrix_test[i] =
            (double *)malloc(n_sensor_t * sizeof(double));
        if (!principal_components_matrix_test[i])
        {
            printf("Error running test case (malloc for element %d failed)\n",
                   i);
            return;
        }

        for (j = 0; j < n_sensor_t; j++)
        {
            principal_components_matrix_test[i][j] = (i + 1);
        }
    }

    printf("\n\n");
    printf("-------------------\n");
    printf("INTEGRATED SUPPORT DEGREE MATRIX TESTING\n");
    printf("-------------------\n");

    calculated_support_matrix =
        calculate_integrated_support_degree_matrix(
            (double **)principal_components_matrix_test,
            contribution_rate_test,
            n_contri_rate_t, n_sensor_t);

    printf("Ensure correctness of calculation ---\n");
    for (int i = 0; i < n_contri_rate_t; i++)
    {
        double result_diff = fabs(expected_support_matrix[i] - calculated_support_matrix[i]);
        if (result_diff > EPSILON)
        {
            ASSERT_TEST(expected_support_matrix[i] ==
                        calculated_support_matrix[i]);
            printf("ERROR: Expected:%f --- Caculated:%f\n", expected_support_matrix[i], calculated_support_matrix[i]);

            free(calculated_support_matrix);
            return;
        }
    }

    printf("PASSED!\n");
    free(calculated_support_matrix);

    for (i = 0; i < n_sensor_t; i++)
    {
        free(principal_components_matrix_test[i]);
    }

    free(principal_components_matrix_test);
}

void automated_eliminate_incorrect_data(void)
{
    double n_sensor_t = 4;
    double parameter = 0.7;
    int res;

    printf("\n\n");
    printf("-------------------\n");
    printf("ELMIMINATE INCORRECT DATA TESTING\n");
    printf("-------------------\n");

    double expected_elminated_matrix[4] = {10.0, 0.0, 3.0, 5.0};
    double input_integrated_support_matrix[4] = {10.0, 1.0, 3.0, 5.0};

    res = eliminate_incorrect_data(input_integrated_support_matrix,
                                   parameter, n_sensor_t);
    if (res < 0)
    {
        printf("Unable to call eliminate_incorrect_data\n");
        ASSERT_TEST(res == 0);
    }
    printf("Ensure correctness of elminination ---\n");

    for (int i = 0; i < n_sensor_t; i++)
    {
        if (expected_elminated_matrix[i] !=
            input_integrated_support_matrix[i])
        {
            printf("ERROR: Expected:%f --- Calculated:%f\n", expected_elminated_matrix[i], input_integrated_support_matrix[i]);
            ASSERT_TEST(expected_elminated_matrix[i] == input_integrated_support_matrix[i]);
            return;
        }
    }

    printf("PASSED!\n");
}

void automated_calculate_weight_coefficient(void)
{
    double n_sensor_t = 4;

    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE WEIGHT COFFICIENT TESTING\n");
    printf("-------------------\n");

    double expected_elminated_matrix[4] = {0.5, 0.0, 0.25, 0.25};
    double input_integrated_support_matrix[4] = {10.0, 0.0, 5.0, 5.0};
    double *caclulated_weight_coefficient;

    caclulated_weight_coefficient = calculate_weight_coefficient(input_integrated_support_matrix,
                                                                 n_sensor_t);
    if (caclulated_weight_coefficient == NULL)
    {
        printf("Unable to call calculate_weight_coefficient\n");
        ASSERT_TEST(caclulated_weight_coefficient != NULL);
    }
    printf("Ensure correctness of elminination ---\n");

    for (int i = 0; i < n_sensor_t; i++)
    {
        double result_diff = fabs(expected_elminated_matrix[i] - caclulated_weight_coefficient[i]);

        if (result_diff > EPSILON)
        {
            printf("ERROR: Expected:%f --- Caculated:%f\n", expected_elminated_matrix[i], caclulated_weight_coefficient[i]);
            ASSERT_TEST(expected_elminated_matrix[i] == caclulated_weight_coefficient[i]);

            free(caclulated_weight_coefficient);
            return;
        }
    }

    free(caclulated_weight_coefficient);
    printf("PASSED!\n");
}

void automated_calculate_fused_output(void)
{
    double n_sensor_t = 4;
    int res;

    printf("\n\n");
    printf("-------------------\n");
    printf("CALCULATE FUSED OUTPUT TESTING\n");
    printf("-------------------\n");

    double expected_fused_output = 7.5;
    double input_sensor_data[] = {10, 1, 5, 5};
    double weight_coefficient[4] = {0.5, 0.0, 0.3, 0.2};
    double caclulated_fused_output;

    res = calculate_fused_output(weight_coefficient,
                                 input_sensor_data, n_sensor_t, &caclulated_fused_output);
    if (res < 0)
    {
        printf("Unable to call calculate_fused_output\n");
        ASSERT_TEST(res == 0);
    }
    printf("Ensure correctness of elminination ---\n");

    if (expected_fused_output != caclulated_fused_output)
    {
        printf("ERROR: Expected:%f --- Calculated:%f\n", expected_fused_output,
               caclulated_fused_output);
        ASSERT_TEST(expected_fused_output == caclulated_fused_output);
        return;
    }

    printf("PASSED!\n");
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
    automated_calculate_integrated_support_degree_matrix();
    automated_eliminate_incorrect_data();
    automated_calculate_weight_coefficient();
    automated_calculate_fused_output();
}
