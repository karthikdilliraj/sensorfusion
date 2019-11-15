

/**
 * Function:    calculate_support_degree_matrix
 *
 * Parameters:
 *  None
 *
 * Calculate Support degree matrix for the set of sensor values
 *
 * Return:
 *  Nothing.
 */
double *calculate_support_degree_matrix (void);

/**
 * Function:    calculate_eigensystem
 *
 * Parameters:
 *  None
 *
 * Calculate eigen value and vectors of the support degree matrix
 *
 * Return:
 *  Nothing.
 */
void calculate_eigensystem (double *support_degree_matrix);

