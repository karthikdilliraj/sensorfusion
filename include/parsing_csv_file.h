#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef Boolean
    #define Boolean int
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define MAX_ROW_LIMIT           1024
#define MAX_SENSOR_NAME_SIZE    255
#define MAX_FILE_NAME_SIZE      255

#define INPUT_MODE  "r"
#define OUTPUT_MODE  "a"

/**
 * Function:    parser_parse_csv_file
 *
 * Parameters:
 *  file_name       [in]    Pointer to file name of CSV to be parsed
 *  lines_to_skip   [in]    Number of lines that have already been parsed
 *  time_in_minutes [out]   Time stamp parsed from CSV converted into minutes
 *                          (hours * 60) + minutes
 *  sensor_name     [out]   Name of the sensor that has been parsed from CSV
 *  sensor_value    [out]   Value of the sensor parsed from the CSV
 *
 * Parses a CSV, one line at a time and returns the time, name and value of
 * that parsed line. Can also skip lines that have been previously parsed.
 *
 * Return:
 *  Whether or not the parser has hit the end of the file
 */
Boolean parser_parse_csv_file(char  *file_name,
                              int   lines_to_skip,
                              int   *time_in_minutes,
                              char  *sensor_name,
                              float *sensor_value);

#endif
