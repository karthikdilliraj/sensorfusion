/**
 * @file calculate_fusion.h
 *
 * @brief A collection of functions related to the calculation of fused output.
 *
 * @author Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca
 * @author Nhat Hieu Le - nhathieule@cmail.carleton.ca
 * @author Jason Miller - jasonmiller@cmail.carleton.ca
 */

#ifndef CALCULATE_FUSION_H
#define CALCULATE_FUSION_H

#include "linked_list.h"

/**
 * @brief Structure to store eigen_systems
 *
 * @details Structure eigen_systems stores pointer to double of eigen_value 
 * and pointer to pointer to double of eigen_vector
 */
struct eigen_systems {
    double *eigen_value;
    /**< Pointer to Eigen Value */

    double **eigen_vector;
    /**< Pointer to multidimensional array of Eigen Vector */
};

/**
 * @brief Calculate Support degree matrix D for the set of sensor values
 *
 *  @param[in]	*node 			Linked list containing sensor values
 *	@param[in]	no_of_sensors	Number of sensor in the Linked list		
 *  @param[out]	*sensor_array 	Array contains sensor values
 *
 *  @return pointer to double of support_degree_matrix, if no, returns NULL.
 *
 */
double *calculate_support_degree_matrix(Node_t *node, int no_of_sensors,
	double *sensor_array);

/**
 * @brief Calculate eigen values and eigen vectors of the support degree matrix
 *
 * @param[in]	*sd_matrix 		Pointer to support degree matrix
 * @param[in]	no_of_sensors	Number of sensors	
 *
 * @return pointer to Structure eigen_systems, if no, returns NULL.
 */
struct eigen_systems *calculate_eigensystem(double *sd_matrix,
	int no_of_sensors);

/**
 * @brief Calculate contribute rate of Principal Component
 *
 * @param[in]	*eigen_value	Pointer to Eigen Value
 * @param[in]	no_of_sensors	Number of sensors
 *
 * @return pointer to double of contribution_rate array, if no, returns NULL.
 */
double *calculate_contribution_rate(double *eigen_value, int no_of_sensors);

/**
 * @brief Determine the number of contribution_rate to use
 *
 * @param[in] *contribution_rate 		Pointer to contribution_rate
 * @param[in] parameter		Parameter of algorithm
 * @param[in] no_of_sensors	Number of sensors	
 *
 * @return number of contribution rate to use, if no, returns -1.
 */
int determine_contribution_rates_to_use(double *contribution_rate,
	float parameter, int no_of_sensors);

/**
 * @brief Calculate the Principal components of the D Matrix
 *
 * @param[in]	*sd_matrix 		Pointer to support degree matrix
 * @param[in]	no_of_sensors	Number of sensors	
 * @param[in]	**eigen_vector	Pointer to multi-dimensional Eigen Vector
 * @param[in]	no_of_contribution_rates_to_use Number of contribution rate
 *
 * @return
 *	Pointer to pointer to double of principal_components_matrix
 *	If no, returns NULL.
 */
double **calculate_principal_components(double *sd_matrix, int no_of_sensors,
	double **eigen_vector, int no_of_contribution_rates_to_use);

/**
 * @brief Calculate the Integrated Support Degree Score for all sensors
 *
 * @param[in] **principle_components	Pointer to principle_components array
 * @param[in] *contribution_rate 		Pointer to contribution_rate
 * @param[in] no_of_contribution_rates_to_use	Number of contribuation rate
 * @param[in] no_of_sensors				Number of sensors
 *
 * @return 
 *	Pointer to Integrated Support Degree Matrix.
 *	If no, returns NULL.
 */
double *calculate_integrated_support_degree_matrix(
	double **principle_components, double *contribution_rate,
	int no_of_contribution_rates_to_use, int no_of_sensors);

/**
 * @brief Eliminate the incorrect sensor data
 *
 * @param[in] *integrate_support_degree_matrix 	Pointer to
 												Integrated Support Degree Matrix
 * @param[in] fault_tolerance	Parameter to remove incorrect data
 * @param[in] no_of_sensors		Number of sensors
 *
 * @return  0 if success, else return negativ.
 */
int eliminate_incorrect_data(double *integrate_support_degree_matrix,
	double fault_tolerance, int no_of_sensors);

/**
 * @brief Calculate the weight coefficients for all sensors
 *
 * @param[in] *integrate_support_degree_matrix 	Pointer to
 												Integrated Support Degree Matrix
 * @param[in] no_of_sensors		Number of sensors
 *
 * @return pointer weight coefficient matrix, if no, returns NULL.
 */
double *calculate_weight_coefficient(double *integrate_support_degree_matrix,
	int no_of_sensors);

/**
 * @brief Calculate the fused output
 *
 * @param[in] 	*weight_coefficient 	Pointer to weight coefficient matrix, 
 * @param[in] 	*sensor_data	 		Array contains sensor values
 * @param[in] 	no_of_sensors			Number of sensors 
 * @param[out]	*fused_value containing fused sensor values
 *
 * @return 0 if success, else returns negative.
 */
double calculate_fused_output(double *weight_coefficient, double *sensor_data,
	int no_of_sensors, double *fused_value);

#endif // CALCULATE_FUSION_H
