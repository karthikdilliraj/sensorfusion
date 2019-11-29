#ifndef SENSOR_H
#define SENSOR_H

#include "linked_list.h"


/**
 * Function:    run_main_sensor_algorithm
 *
 * Parameters:
 *  *in_file_name   [in]    Pointer to the filename of the file that contains
 *                          the data to run the sensor fusion algorithm on.
 *  *out_file_name  [in]    Pointer to the filename of the file that will
 *                          contain the output data from the sensor fusion
 *                          algorithm.
 *  high_range      [in]    The high limit the user has specified.
 *  use_high_range  [in]    Whether or not the user has specified a high sensor
 *                          limit.
 *  low_range       [in]    The low limit the user has specified
 *  use_low_range   [in]    Whether or not the user has specified a low sensor
 *                          limit.
 *  stuck_range     [in]    The stuck interval the user has specified
 *  use_stuck       [in]    Whether or not the user has specified a stuck limit.
 *
 * Starts off the sensor algorithm by reading in the values from the CSV file
 * specified by *in_file_name.
 *
 * Return:
 *  Nothing
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
 * Function:    update_sensor_lists
 *
 * Parameters:
 *  time_in_minutes [in]    Time in minutes, read from the input file
 *  *sensor_name    [in]    Sensor name, read from the input file
 *  sensor_value    [in]    Sensor value, read from the input file
 *  use_high_range  [in]    Whether or not the user has specified a high sensor
 *                          limit.
 *  high_range      [in]    The limit the user has specified
 *  use_low_range   [in]    Whether or not the user has specified a low sensor
 *                          limit.
 *  low_range       [in]    The limit the user has specified
 *
 * Updates the Valid and Out of Range sensor lists.
 *
 * Return:
 *  Nothing
 */
void update_sensor_lists(int    time_in_minutes,
                         char   *sensor_name,
                         float  sensor_value,
                         int    use_high_range,
                         int    high_range,
                         int    use_low_range,
                         int    low_range);


/**
 * Function:    search_all_chains
 *
 * Parameters:
 *  *str        [in]    Sensor name to search for
 *  *list_index [out]   Index of the chain that str was found in.
 *
 * Searches all linked list chains for a node containing a sensor name of *str.
 * If found, will put the list index in which the node was found into
 * *list_index and return a valid Node_t object.
 *
 * Return:
 *  Pointer to the matching node, if no node is found, returns NULL.
 */
Node_t* search_all_chains(char *str, int *list_index);


/**
 * Function:    determine_if_sensors_are_stuck
 *
 * Parameters:
 *  current_time    [in]    The current time with respect to where the parser
 *                          is within the input.csv file.
 *  stuck_value     [in]    User specified limit for determining stuck sensors.
 *
 * Iterates through the valid sensor list and the out of range sensor list to
 * see if any sensors have not been updated within an interval of stuck_value.
 * If so, will move that node from its current list into the stuck sensor list.
 *
 * Return:
 *  Nothing.
 */
void determine_if_sensors_are_stuck(int current_time, int stuck_value);


/**
 * Function:    dump_current_lists
 *
 * Parameters:
 *  Nothing
 *
 * A compact dump of all the nodes contained within all the linked lists.
 *
 * Return:
 *  Nothing.
 */
void dump_current_lists(void);


/**
 * Function:    write_output_file
 *
 * Parameters:
 *  *file_name          [in]    Pointer to the filename of the file that will
 *                              contain the output data from the sensor fusion
 *                              algorithm.
 *  use_high_range      [in]    Whether or not the user has specified a high
 *                              sensor limit.
 *  high_range          [in]    The high limit the user has specified.
 *  use_low_range       [in]    Whether or not the user has specified a low
 *                              sensor limit.
 *  low_range           [in]    The low limit the user has specified
 *  use_stuck           [in]    Whether or not the user has specified a stuck
 *                              limit.
 *  stuck_range         [in]    The stuck interval the user has specified
 *` current_time        [in]    The time within the CSV the parser is currently
 *                              looking at.
 *  fused_sensor_value  [in]    The final fused sensor value returned by the
 *                              sensor fusion algorithm.
 *
 * Writes the final sensor fusion report to file.
 *
 * Return:
 *  Nothing
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
 * Function:    do_sensor_fusion_algorithm
 *
 * Parameters:
 *  None
 *
 * Entry point to the Fused Sensor Algorithm
 *
 * Return:
 *  The fused sensor value after, the algorithm has been run.
 */
float do_sensor_fusion_algorithm(void);

#endif
