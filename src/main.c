/**
 * Implementation of the main portion of the Fused Sensor Calculator.
 */

#include <stdio.h>
#include <stdlib.h>
#include "parsing_csv_file.h"
#include "calculate_fusion.h"
#include "sensor.h"
/**
 * Uncomment this and the function call start_automated_testing once the test
 *  Makefile has been made
 *
 * #include "test.h"
 */

/**
 * Currently, the exe gets put into sensorfusion/bin directory, but the input
 * file is in sensorfusion/src, so we will go down one directory, and up into
 * src to find the file.
 */
#define INPUT_FILE_NAME "src/input.csv"
#define OUTPUT_FILE_NAME "sensor_fusion_report.txt"

int main(int argc, char *argv[])
{
    Boolean use_high_range = FALSE;
    Boolean use_low_range = FALSE;
    Boolean use_stuck = FALSE;
    float   high_range;
    float   low_range;
    char    in_file_name[MAX_FILE_NAME_SIZE];
    char    out_file_name[MAX_FILE_NAME_SIZE];
    int     opt;
    int     stuck_range;

    /**
     * Run testing for calculate_fusion.c
     */
    
    struct support_degree_matrix spd = calculate_support_degree_matrix();
    struct eigen_systems eigen = calculate_eigensystem(spd);
    double *contribution_rate = calculate_contribution_rate(eigen, spd.no_of_sensors);
    int no_of_contribution_rates_to_use = determine_contribution_rates_to_use(contribution_rate, 0.5, spd.no_of_sensors);
    double **principal_components_matrix = calculate_principal_components(spd, eigen.eigen_vector, no_of_contribution_rates_to_use);

    /**
     * Run testing for step 6 to step 9
     */
    double contribution_rate_test[] = {0.1, 0.2, 0.3, 0.4};
    double n_sensor_t = 4;
    double n_contri_rate_t = 3;

    double **principal_components_matrix_test = (double **)malloc(n_sensor_t * sizeof(double *)); 
    for (int i = 0; i < n_sensor_t; i++)
    {
         principal_components_matrix_test[i] = (double *)malloc(n_sensor_t * sizeof(double)); 
    }

    double count = 0; 
    for (int i = 0; i < n_sensor_t; i++)
    {
      for (int j = 0; j < n_sensor_t; j++)
      {
         principal_components_matrix_test[i][j] = ++count;
      }
    }

    printf("calculate_integrated_support_degree_matrix\n");
    double *integrate_support_matrix =
        calculate_integrated_support_degree_matrix(principal_components_matrix_test,
            contribution_rate_test, n_contri_rate_t, n_sensor_t);

    if (integrate_support_matrix == NULL)
    {
        goto calculate_done;
    }

    printf("integrate_support_matrix: ");
    for (int idx = 0; idx < n_sensor_t; idx++)
    {
        printf(" %f", integrate_support_matrix[idx]);
    }
    printf("\n");

    int res = eliminate_incorrect_data(integrate_support_matrix, 0.7, n_sensor_t);
    if (res != 0) {
        printf("Fail to eliminate incorrect data\n");
        goto calculate_done;
    }

    printf("Eliminated integrate_support_matrix: ");
    for (int idx = 0; idx < n_sensor_t; idx++)
    {
        printf(" %f", integrate_support_matrix[idx]);
    }
    printf("\n");

    double *weight_coff = calculate_weight_coefficient(integrate_support_matrix, n_sensor_t);
    if (weight_coff == NULL)
    {
        goto calculate_done;
    }

    printf("Weight Coefficient: ");
    for (int idx = 0; idx < n_sensor_t; idx++)
    {
        printf(" %f", weight_coff[idx]);
    }
    printf("\n");

    double sensor_data_t[] = {10, 1, 4 ,5};
    double fused_value = calculate_fused_output(weight_coff, sensor_data_t, n_sensor_t);
    printf("Fused value:%f\n", fused_value);

calculate_done:

    strncpy(in_file_name, INPUT_FILE_NAME, MAX_FILE_NAME_SIZE);
    strncpy(out_file_name, OUTPUT_FILE_NAME, MAX_FILE_NAME_SIZE);

    while((opt = getopt(argc, argv, "htl:u:s:f:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("\n\n");
                printf("Usage: sensorfusion.exe [-h] [-t] [-l] [-u] [-s] [-f]"
                       "\n\n");
                printf("Usage:\n");
                printf("    -h              Prints this message and exits\n");
                printf("    -t              Runs automated unit testing and "
                       "exits\n");
                printf("    -l value        Specifies the lower limit below "
                       "which the sensor will be\n                    marked "
                       "out of range.\n");
                printf("    -u value        Specifies the upper limit above "
                       "which the sensor will be\n                    marked "
                       "out of range.\n");
                printf("    -s value        Specifies how long (in minutes) "
                       "beyond which, the sensor\n                    is "
                       "considered to be stuck, and no longer valid.\n");
                printf("    -f file_name    Specifies a non-default input file"
                       "path.\n");
            return 0;
            break;
            case 't':
                /* Run automated unit testing */
                printf("Running automated unit testing\n");
                printf("\n\nAUTOMATED TESTING NOT YET IMPLEMENTED. MAKEFILE IS "
                       "REQUIRED\n\n");
                /**
                 * Uncomment this once the test Makefile has been created. Also
                 * uncomment the includes on line 12.
                 *
                 * start_automated_testing();
                 */
                printf("Automated testing has completed\n");
                return 0;
                break;
            case 'l':
                /**
                 * Specifies the low edge of the valid sensor range. If the
                 * sensor value is below this, it goes into the out of range
                 * sensor list.
                 */
                low_range = strtod(optarg, NULL);
                use_low_range = TRUE;
                break;
            case 'u':
                /**
                 * Specifies the high edge of the valid sensor range. If the
                 * sensor value is above this, it goes into the out of range
                 * sensor list.
                 */
                high_range = strtod(optarg, NULL);
                use_high_range = TRUE;
                break;
            case 's':
                /**
                 * Specifies how long (in minutes) beyond which, the sensor is
                 * considered to be stuck, and no longer valid.
                 */
                stuck_range = strtod(optarg, NULL);
                use_stuck = TRUE;
                break;
            case 'f':
                /**
                 * Specifies a non-default input file to use for the sensor
                 * input data.
                 */
                strncpy(in_file_name, optarg, MAX_FILE_NAME_SIZE);
                break;
            default:
                printf("sensorfusion usage: sensorfusion.exe [-htlusf]\n");
                break;
        }
    }

    run_main_sensor_algorithm(in_file_name,
                              out_file_name,
                              high_range,
                              use_high_range,
                              low_range,
                              use_low_range,
                              stuck_range,
                              use_stuck);

    return 0;
}