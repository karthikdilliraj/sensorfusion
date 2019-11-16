struct support_degree_matrix
{
    double *sd_matrix;
    int no_of_sensors;
};

struct eigen_systems
{
    double *eigen_value;
    double **eigen_vector;
};

/**
 * Function:    calculate_support_degree_matrix
 *
 * Parameters:
 *  None
 *
 * Calculate Support degree matrix D for the set of sensor values
 *
 * Return:
 *  Structure support_degree_matrix.
 */
struct support_degree_matrix calculate_support_degree_matrix(void);

/**
 * Function:    calculate_eigensystem
 *
 * Parameters:
 *  Structure support_degree_matrix
 *
 * Calculate eigen values and vectors of the support degree matrix
 *
 * Return:
 *  Structure eigen_systems.
 */
struct eigen_systems calculate_eigensystem(struct support_degree_matrix spd);

/**
 * Function:    calculate_contribution_rate
 *
 * Parameters:
 *  Structure eigen_systems, int no_of_sensors
 *
 * Calculate contribute rate of Principal component
 *
 * Return:
 *  double * contribution_rate.
 */
double *calculate_contribution_rate(struct eigen_systems eigen, int no_of_sensors);

/**
 * Function:    determine_contribution_rates_to_use
 *
 * Parameters:
 *  double * contribution_rate, float parameter, int no_of_sensors
 *
 * Determine the number of contribution_rate to use
 *
 * Return:
 *  int no_of_contribution_rates_to_use.
 */
int determine_contribution_rates_to_use(double *contribution_rate, float parameter, int no_of_sensors);

/**
 * Function:    determine_contribution_rates_to_use
 *
 * Parameters:
 *  Structure support_degree_matrix, double ** eigen_vector, int no_of_contribution_rates_to_use
 *
 * Calculate the Principal components of the D Matrix
 *
 * Return:
 *  double ** principal_components_matrix.
 */
double **calculate_principal_components(struct support_degree_matrix spd, double **eigen_vector, int no_of_contribution_rates_to_use);
