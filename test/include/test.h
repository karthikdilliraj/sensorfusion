/**
 * @file test.h
 *
 * @brief Collections of declaration function of automated unit tests.
 *
 * @author Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca
 * @author Nhat Hieu Le - nhathieule@cmail.carleton.ca
 * @author Jason Miller - jasonmiller@cmail.carleton.ca
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sensor.h"
#include "calculate_fusion.h"

/**
 * @brief Epsilon to compare two float or double value
 */
#define EPSILON 0.0001

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

/**
 * @brief Automated unit testing of calculate_support_degree_matrix
 *
 * @details Automatically tests the support degree matrix calculation by 
 * parsing the the sensor values
 */
void automated_calculate_support_degree_matrix(void);

/**
 * @brief Automated unit testing of calculate_eigensystem
 *
 * @details Automatically tests the eigensystem calculation by the input of
 * support degree matrix
 */
void automated_calculate_eigensystem(void);

/**
 * @brief Automated unit testing of calculate_contribution_rate
 *
 * @details Automatically tests the contribute rate calculation by the input of
 * eigensystem values and number of sensors
 */
void automated_calculate_contribution_rate(void);

/**
 * @brief Automated unit testing of determine_contribution_rates_to_use
 *
 * @details Automatically tests the contribute rates to be used calculation by 
 * the input of contribution rate, parameter and number of sensors
 */
void automated_determine_contribution_rates_to_use(void);

/**
 * @brief Automated unit testing of calculate_principal_components
 *
 * @details Automatically tests the principal components calculation by the 
 * input of support_degree_matrix, eigenvector and number of contribution rates
 * to use
 */
void automated_calculate_principal_components(void);

/**
 * @brief Automated unit testing of calculate_integrated_support_degree_matrix
 *
 * @details Automatically tests the integrated support degree matrix calculation
 * by the input of principal_components_matrix, number of contribution rates to 
 * use and number of sensors
 */
void automated_calculate_integrated_support_degree_matrix(void);

/**
 * @brief Automated unit testing of eliminate_incorrect_data
 *
 * @details Automatically tests elimination of incorrect data within integrate
 * support degree matrix by the input of integrated_support_degree_matrix, 
 * number of sensors and the fault tolerance parameters
 */
void automated_eliminate_incorrect_data(void);

/**
 * @brief Automated unit testing of calculate_weight_coefficient
 *
 * @details Automatically tests weight coefficient matrix by the input of
 * elminianated integrated_support_degree_matrix, number of sensors
 */
void automated_calculate_weight_coefficient(void);

/**
 * @brief Automated unit testing of calculate_fused_output
 *
 * @details Automatically tests fused sensor output by the input of
 * weight coefficient matrix, the raw sensor data and the number of sensors
 */
void automated_calculate_fused_output(void);

#endif
