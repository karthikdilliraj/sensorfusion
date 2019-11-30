/**
 * @file parsing_csv_file.h
 *
 * @brief Implementation of the CSV parser.
 */
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief Define a boolean data type.
 */
#ifndef Boolean
    #define Boolean int
#endif

/**
 * @brief Define a boolean True.
 */
#ifndef TRUE
    #define TRUE 1
#endif

/**
 * @brief Define a boolean False.
 */
#ifndef FALSE
    #define FALSE 0
#endif

/**
 * @brief Maximum number of rows supported in a CSV.
 */
#define MAX_ROW_LIMIT           1024

/**
 * @brief Maximum length of a sensor name.
 */
#define MAX_SENSOR_NAME_SIZE    255

/**
 * @brief Maximum length of a file name.
 */
#define MAX_FILE_NAME_SIZE      255

/**
 * @brief Input mode of file is read.
 */
#define INPUT_MODE  "r"

/**
 * @brief Will append to existing file when writing to it.
 */
#define OUTPUT_MODE  "a"

/**
 * @brief Parses CSV file
 *
 * @param[in]  *file_name       Pointer to file name of CSV to be parsed
 * @param[in]  lines_to_skip    Number of lines that have already been parsed
 * @param[out] *time_in_minutes Time stamp parsed from CSV converted into   
 *                              minutes (hours * 60) + minutes
 * @param[out] *sensor_name     Name of the sensor that has been parsed from
 *                              CSV
 * @param[out] *sensor_value    Value of the sensor parsed from the CSV
 *
 * @details Parses a CSV, one line at a time and returns the time, name and 
 * value of that parsed line. Can also skip lines that have been previously 
 * parsed.
 *
 * @return Whether or not the parser has hit the end of the file
 */
Boolean parser_parse_csv_file(char  *file_name,
                              int   lines_to_skip,
                              int   *time_in_minutes,
                              char  *sensor_name,
                              float *sensor_value);

#endif
