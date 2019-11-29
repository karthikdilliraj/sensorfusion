/**
 * Implementation of the main portion of the Fused Sensor Calculator.
 */

#include <stdio.h>
#include <stdlib.h>
#include "parsing_csv_file.h"
#include "eigensystems.h"
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
     * Run testing for eigensystems.c
     */
    eigensystems_test();

    strncpy(in_file_name, INPUT_FILE_NAME, MAX_FILE_NAME_SIZE);
    strncpy(out_file_name, OUTPUT_FILE_NAME, MAX_FILE_NAME_SIZE);

    while((opt = getopt(argc, argv, "htl:u:s:f:")) != -1)
    {
        switch(opt)
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



