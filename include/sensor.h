/**
 * @file sensor.h
 *
 * @brief A collection of functions related to the manipulation of sensors.
 */
 
#ifndef SENSOR_H
#define SENSOR_H

#include "linked_list.h"
#include "calculate_fusion.h"


/**
 * @brief Starts the sensor fusion algorithm by parsing the CSV
 *
 * @param[in] *in_file_name    Pointer to the filename of the file that 
 *                             contains the data to run the sensor fusion
 *                             algorithm on.
 * @param[in] *out_file_name   Pointer to the filename of the file that will
 *                             contain the output data from the sensor fusion
 *                             algorithm.
 * @param[in] high_range       The high limit the user has specified.
 * @param[in] use_high_range   Whether or not the user has specified a high 
 *                             sensor limit.
 * @param[in] low_range        The low limit the user has specified
 * @param[in] use_low_range    Whether or not the user has specified a low 
 *                             sensor limit.
 * @param[in] stuck_range      The stuck interval the user has specified
 * @param[in] use_stuck        Whether or not the user has specified a stuck
 *                             limit.
 *
 * @details Starts off the sensor algorithm by reading in the values from the 
 * CSV file specified by *in_file_name.
 */
void run_main_sensor_algorithm(char     *in_file_name,
                               char     *out_file_name,
                               float    high_range,
                               Boolean  use_high_range,
                               float    low_range,
                               Boolean  use_low_range,
                               float    stuck_range,
                               Boolean  use_stuck);


/**
 * @brief Updates sensors in linked lists
 *
 * @param[in] time_in_minutes  Time in minutes, read from the input file
 * @param[in] *sensor_name     Sensor name, read from the input file
 * @param[in] sensor_value     Sensor value, read from the input file
 * @param[in] use_high_range   Whether or not the user has specified a high 
 *                             sensor limit.
 * @param[in] high_range       The limit the user has specified
 * @param[in] use_low_range    Whether or not the user has specified a low 
 *                             sensor limit.
 * @param[in] low_range        The limit the user has specified
 *
 * @details Updates the Valid and Out of Range sensor lists.
 */
void update_sensor_lists(int    time_in_minutes,
                         char   *sensor_name,
                         float  sensor_value,
                         int    use_high_range,
                         int    high_range,
                         int    use_low_range,
                         int    low_range);


/**
 * @brief Search all lists for a node with a name of *str
 *
 * @param[in]   *str        Sensor name to search for
 * @param[out]  *list_index Index of the chain that str was found in.
 *
 * @details Searches all linked list chains for a node containing a sensor name 
 * of *str. If found, will put the list index in which the node was found into
 * *list_index and return a valid Node_t object.
 *
 * @return Pointer to the matching node, if no node is found, returns NULL.
 */
Node_t* search_all_chains(char *str, int *list_index);


/**
 * @brief Moves sensors into stuck list if needed
 *
 * @param[in] current_time  The current time with respect to where the parser
 *                          is within the input.csv file.
 * @param[in] stuck_value   User specified limit for determining stuck sensors.
 *
 * @details Iterates through the valid sensor list and the out of range sensor 
 * list to see if any sensors have not been updated within an interval of 
 * stuck_value.If so, will move that node from its current list into the stuck
 * sensor list.
 */
void determine_if_sensors_are_stuck(int current_time, int stuck_value);


/**
 * @brief Display contents of all nodes
 *
 * @details A compact dump of all the nodes contained within all the linked
 * lists.
 */
void dump_current_lists(void);


/**
 * @brief Writes output file
 *
 * @param[in] *file_name            Pointer to the filename of the file that 
 *                                  will contain the output data from the 
 *                                  sensor fusion algorithm.
 * @param[in] use_high_range        Whether or not the user has specified a 
 *                                  high sensor limit.
 * @param[in] high_range            The high limit the user has specified.
 * @param[in] use_low_range         Whether or not the user has specified a low
 *                                  sensor limit.
 * @param[in] low_range             The low limit the user has specified
 * @param[in] use_stuck             Whether or not the user has specified a 
 *                                  stuck limit.
 * @param[in] stuck_range           The stuck interval the user has specified
 *`@param[in] current_time          The time within the CSV the parser is 
 *                                  currently looking at.
 * @param[in] fused_sensor_value    The final fused sensor value returned by 
 *                                  the sensor fusion algorithm.
 *
 * @details Writes the final sensor fusion report to file.
 */
void write_output_file(char     *file_name,
                       int      use_high_range,
                       float    high_range,
                       int      use_low_range,
                       float    low_range,
                       int      use_stuck,
                       int      stuck_range,
                       int      current_time,
                       float    fused_sensor_value);


/**
 * @brief Starts the sensor fusion algorithm
 *
 * @details Entry point to the Fused Sensor Algorithm
 *
 * @return The fused sensor value after, the algorithm has been run.
 */
float do_sensor_fusion_algorithm(void);

#endif
