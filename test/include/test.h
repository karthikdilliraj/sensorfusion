#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sensor.h"


/**
 * Function:    start_automated_testing
 *
 * Parameters:
 *   None
 *
 * Entry point into the automated test script
 *
 * Return:
 *  Nothing
 */
void start_automated_testing(void);


/**
 * Function:    automated_testing_linked_list
 *
 * Parameters:
 *   None
 *
 * Automatically tests the linked list functions by doing the following:
 *  - Add a few nodes to a linked list
 *  - Update a few nodes in a linked list
 *  - Count how many nodes are in a linked list
 *  - Move from one linked list to another linked list
 *  - Delete from the middle of a linked list
 *  - Delete from the start of a linked list
 *  - Delete from the end of a linked list
 *
 * Return:
 *  Nothing
 */
void automated_testing_linked_list(void);


/**
 * Function:    automated_testing_csv_parsing
 *
 * Parameters:
 *   None
 *
 * Automatically tests the CSV parser by parsing the first 4 lines of the test
 * CSV file and ensuring they are expected values.
 *
 * Return:
 *  Nothing
 */
void automated_testing_csv_parsing(void);


/**
 * Function:    automated_sensor_manipulation
 *
 * Parameters:
 *   None
 *
 * Automatically tests the sensor list manipulation by parsing the whole test
 * CSV and determining what list it belongs into.
 *
 * Return:
 *  Nothing
 */
void automated_sensor_manipulation(void);

#endif