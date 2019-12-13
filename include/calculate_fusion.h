/**
 * @brief A collection of functions related to the calculation of fused output.
 */

#ifndef CALCULATE_FUSION_H
#define CALCULATE_FUSION_H

#include "linked_list.h"

/**
 * @brief Structure to store support_degree_matrix
 *
 * @details Structure support_degree_matrix stores pointer to double of sd_matrix and int no_of_sensors
 */

struct support_degree_matrix
{
    double *sd_matrix;
    int no_of_sensors;
};

/**
 * @brief Structure to store eigen_systems
 *
 * @details Structure eigen_systems stores pointer to double of eigen_value and pointer to pointer to double of eigen_vector
 */
struct eigen_systems
{
    double *eigen_value;
    double **eigen_vector;
};

/**
 * @brief Calculate Support degree matrix D for the set of sensor values
 *
 *  @param[in]   Node_t *node Linked list containing sensor values
 * 
 *  @return pointer to Structure support_degree_matrix, if no node is found, returns NULL.
 * 
 */

struct support_degree_matrix *calculate_support_degree_matrix(Node_t *node);
/**
 * @brief Calculate eigen values and eigen vectors of the support degree matrix
 *
 * @param[in] pointer to Structure support_degree_matrix spd
 *
 * @return pointer to Structure eigen_systems, if input is invalid, returns NULL.
 */

struct eigen_systems *calculate_eigensystem(struct support_degree_matrix *spd);

/**
 * @brief Calculate contribute rate of Principal component
 *
 * @param[in] pointer to Structure eigen_systems eigen, int no_of_sensors
 *
 * @return pointer to double of contribution_rate, if input is invalid, returns NULL.
 */

double *calculate_contribution_rate(struct eigen_systems *eigen, int no_of_sensors);

/**
 * @brief Determine the number of contribution_rate to use
 *
 * @param[in] pointer to double of contribution_rate, float parameter, int no_of_sensors
 *
 * @return int no_of_contribution_rates_to_use, if input is invalid, returns -1.
 */

int determine_contribution_rates_to_use(double *contribution_rate, float parameter, int no_of_sensors);

/**
 * @brief Calculate the Principal components of the D Matrix
 *
 * @param[in] pointer to Structure support_degree_matrix spd, pointer to pointer to double of eigen_vector, int no_of_contribution_rates_to_use
 *
 * @return pointer to pointer to double of principal_components_matrix, if input is invalid, returns NULL.
 */

double **calculate_principal_components(struct support_degree_matrix *spd, double **eigen_vector, int no_of_contribution_rates_to_use);

/**
 * @brief Calculate the Integrated Support Degree Score for all sensors
 *
 * @param[in] pointer to pointer to double of principle_components, pointer to double of contribution_rate, int no_of_contribution_rates_to_use, int no_of_sensors
 *
 * @return pointer to double of calculate_integrated_support_degree_matrix, if input is invalid, returns NULL.
 */

double *calculate_integrated_support_degree_matrix(double **principle_components, double *contribution_rate, int no_of_contribution_rates_to_use, int no_of_sensors);

/**
 * @brief Eliminate the incorrect sensor data
 *
 * @param[in] pointer to double of integrate_support_degree_matrix, double fault_tolerance, int no_of_sensors
 *
 * @return int integrate_support_degree_matrix, if input is invalid, returns NULL.
 */

int eliminate_incorrect_data(double *integrate_support_degree_matrix, double fault_tolerance, int no_of_sensors);

/**
 * @brief Calculate the weight coefficients for all sensors
 *
 * @param[in] pointer to double of integrate_support_degree_matrix, int no_of_sensors
 *
 * @return pointer to double of calculate_weight_coefficient, if input is invalid, returns NULL.
 */

double *calculate_weight_coefficient(double *integrate_support_degree_matrix, int no_of_sensors);

/**
 * @brief Calculate the fused output
 *
 * @param[in] pointer to double of weight_coefficient, pointer to double of sensor_data, int no_of_sensors
 *
 * @return double calculate_fused_output, if input is invalid, returns NULL.
 */

int calculate_fused_output(double *weight_coefficient, double *sensor_data, int no_of_sensors, double *fused_value);

#endif // CALCULATE_FUSION_H