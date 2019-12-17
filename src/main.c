/**
 * @file main.c
 *
 * @brief Implementation of the main portion of the Fused Sensor Calculator.
 *
 * @author Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca - Carleton University
 * @author Nhat Hieu Le - nhathieule@cmail.carleton.ca - Carleton University
 * @author Jason Miller - jasonmiller@cmail.carleton.ca - Carleton University
 */

#include <stdio.h>
#include <stdlib.h>
#include "parsing_csv_file.h"
#include "calculate_fusion.h"
#include "sensor.h"
#include "test.h"

/*
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
    float high_range;
    float low_range;
    char in_file_name[MAX_FILE_NAME_SIZE];
    char out_file_name[MAX_FILE_NAME_SIZE];
    int opt;
    int stuck_range;
    int q_support_value = 0;
    int principal_component_ratio = 100;

    strncpy(in_file_name, INPUT_FILE_NAME, MAX_FILE_NAME_SIZE);
    strncpy(out_file_name, OUTPUT_FILE_NAME, MAX_FILE_NAME_SIZE);

    while ((opt = getopt(argc, argv, "htl:u:s:f:q:p:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("\n\n");
            printf("Usage: sensorfusion.exe [-f] [-h] [-l] [-p] [-q] [-s] [-t]"
                   " [-u]\n\n");
            printf("Usage:\n");
            printf("    -f file_name    Specifies a non-default input file"
                   "path.\n");
            printf("    -h              Prints this message and exits\n");
            printf("    -l value        Specifies the lower limit below "
                   "which the sensor will be\n                    marked "
                   "out of range.\n");
            printf("    -p value        Specifies the ratio used to determine "
                   "how many principle\n                    components are "
                   "to be used\n");
            printf("    -q value        Specifies the percentage of sensors "
                   "that must agree\n                    before a sensor value "
                   "is considered valid.\n                    This is input as "
                   "a percentage * 100.\n");
            printf("    -s value        Specifies how long (in minutes) "
                   "beyond which, the sensor\n                    is "
                   "considered to be stuck, and no longer valid.\n");
            printf("    -t              Runs automated unit testing and "
                   "exits\n");
            printf("    -u value        Specifies the upper limit above "
                   "which the sensor will be\n                    marked "
                   "out of range.\n");
            return 0;
            break;
        case 't':
            /* Run automated unit testing */
            printf("Running automated unit testing\n");
            start_automated_testing();
            printf("Automated testing has completed\n");
            return 0;
            break;
        case 'l':
            /*
             * Specifies the low edge of the valid sensor range. If the
             * sensor value is below this, it goes into the out of range
             * sensor list.
             */
            low_range = strtod(optarg, NULL);
            use_low_range = TRUE;
            break;
        case 'u':
            /*
             * Specifies the high edge of the valid sensor range. If the
             * sensor value is above this, it goes into the out of range
             * sensor list.
             */
            high_range = strtod(optarg, NULL);
            use_high_range = TRUE;
            break;
        case 's':
            /*
             * Specifies how long (in minutes) beyond which, the sensor is
             * considered to be stuck, and no longer valid.
             */
            stuck_range = strtod(optarg, NULL);
            use_stuck = TRUE;
            break;
        case 'f':
            /*
             * Specifies a non-default input file to use for the sensor
             * input data.
             */
            strncpy(in_file_name, optarg, MAX_FILE_NAME_SIZE);
            break;
        case 'q':
            /*
             * Specifies the q-support value - what percentage of sensors need
             * to agree for a sensor to be accepted. This is input as a whole
             * number (percentage * 100). By default, if this is not specified,
             * then no sensors need to agree.
             */
            q_support_value = strtod(optarg, NULL);
            if ((q_support_value < 0) || (q_support_value > 100))
            {
                printf("Error, q_support (-q) must be between 0 - 100\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'p':
            /*
             * Specifies the p-ratio - this ratio is used to determine how many 
             * principal components are to be used.
             */
            principal_component_ratio = strtod(optarg, NULL);
            if ((principal_component_ratio < 0) ||
                (principal_component_ratio > 100))
            {
                printf("Error, principal ratio (-p) must be between 0 - 100\n");
                exit(EXIT_FAILURE);
            }
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
                              use_stuck,
                              q_support_value,
                              principal_component_ratio);

    return 0;
}