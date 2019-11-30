/**
 * @file test.h
 *
 * @brief Implementation of automated unit tests.
 */
 
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sensor.h"


/**
 * @brief Starts automated testing
 *
 * @details Entry point into the automated test script
 */
void start_automated_testing(void);


/**
 * @brief Automated unit testing of linked list subsystem
 *
 * @details Automatically tests the linked list functions by doing the 
 * following:
 *  - Add a few nodes to a linked list
 *  - Update a few nodes in a linked list
 *  - Count how many nodes are in a linked list
 *  - Move from one linked list to another linked list
 *  - Delete from the middle of a linked list
 *  - Delete from the start of a linked list
 *  - Delete from the end of a linked list
 */
void automated_testing_linked_list(void);


/**
 * @brief Automated testing of CSV parser
 *
 * @details Automatically tests the CSV parser by parsing the first 4 lines of 
 * the test CSV file and ensuring they are expected values.
 */
void automated_testing_csv_parsing(void);


/**
 * @brief Automated unit testing of sensor manipulation subsystem
 *
 * @details Automatically tests the sensor list manipulation by parsing the 
 * whole test CSV and determining what list it belongs into.
 */
void automated_sensor_manipulation(void);

#endif