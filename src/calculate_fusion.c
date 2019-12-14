#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "calculate_fusion.h"

double *calculate_support_degree_matrix(Node_t *node, int no_of_sensors, double *sensor_array)
{
    if (node == NULL)
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    int i = 0;

    while (node != NULL)
    {
        sensor_array[i] = node->sensor_value;
        node = node->next;
        i++;
    }
    double *sd_matrix;
    double **arrptr = (double **)malloc(no_of_sensors * sizeof(double *));
    int count = 0;
    for (int i = 0; i < no_of_sensors; i++)
    {
        arrptr[i] = (double *)malloc(no_of_sensors * sizeof(double));
    }
    sd_matrix = (double *)malloc(sizeof(double) * no_of_sensors * no_of_sensors);
    if (arrptr == NULL || sd_matrix == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }

    printf("---- Step1   ====Spd_matrix:\n");
    for (int i = 0; i < no_of_sensors; i++)
    {
        for (int j = 0; j < no_of_sensors; j++)
        {
            arrptr[i][j] = exp(-1 * fabs(sensor_array[i] - sensor_array[j]));
            sd_matrix[count] = arrptr[i][j];
            count++;
            printf("%f ", arrptr[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i< no_of_sensors; i++){
        free(arrptr[i]);
    }
    free(arrptr);
    return sd_matrix;
}

struct eigen_systems *calculate_eigensystem(double *sd_matrix, int no_of_sensors)
{
    if (sd_matrix == NULL || no_of_sensors == 0)
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    struct eigen_systems *eigen;
    eigen = (struct eigen_systems *)malloc(sizeof(struct eigen_systems));
    eigen->eigen_value = (double *)malloc(sizeof(double) * no_of_sensors);
    eigen->eigen_vector = (double **)malloc(no_of_sensors * sizeof(double *));
    for (int i = 0; i < no_of_sensors; i++)
    {
        eigen->eigen_vector[i] = (double *)malloc(no_of_sensors * sizeof(double));
    }
    if (eigen == NULL || eigen->eigen_vector == NULL || eigen->eigen_value == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }
    gsl_matrix_view m = gsl_matrix_view_array(sd_matrix, no_of_sensors, no_of_sensors);

    gsl_vector *eval = gsl_vector_alloc(no_of_sensors);
    gsl_matrix *evec = gsl_matrix_alloc(no_of_sensors, no_of_sensors);

    gsl_eigen_symmv_workspace *w =
        gsl_eigen_symmv_alloc(no_of_sensors);

    gsl_eigen_symmv(&m.matrix, eval, evec, w);

    gsl_eigen_symmv_free(w);

    gsl_eigen_symmv_sort(eval, evec,
                         GSL_EIGEN_SORT_VAL_DESC);

    printf("---- Step 2 -----\n");
    for (int i = 0; i < no_of_sensors; i++)
    {
        eigen->eigen_value[i] = gsl_vector_get(eval, i);
        printf("===Eigen Value: %f\n", eigen->eigen_value[i]);

        gsl_vector_view evec_i = gsl_matrix_column(evec, i);
        printf("===Eigen Vector:\n");
        for (int j = 0; j < no_of_sensors; j++)
        {
            eigen->eigen_vector[i][j] = *(*(&evec_i.vector.data) + j * no_of_sensors);
            printf("%f ", eigen->eigen_vector[i][j]);
        }
        printf("\n");
    }
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    return eigen;
}

double *calculate_contribution_rate(double *eigen_value, int no_of_sensors)
{
    if (eigen_value == NULL || no_of_sensors == 0)
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    double *contribution_rate = (double *)malloc(no_of_sensors * sizeof(double));
    if (contribution_rate == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }
    double sum = 0;
    for (int i = 0; i < no_of_sensors; i++)
    {
        sum += eigen_value[i];
    }

    printf("---- Step4 ----\n");
    printf("=Contribution_rate: \n");
    for (int j = 0; j < no_of_sensors; j++)
    {
        contribution_rate[j] = eigen_value[j] / sum;
        printf("%f ", contribution_rate[j]);
    }
    printf("\n");
    return contribution_rate;
}

int determine_contribution_rates_to_use(double *contribution_rate, float parameter, int no_of_sensors)
{
    if ((contribution_rate == NULL) || (parameter == 0) || (no_of_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return -1;
    }
    double sum = 0;
    int no_of_contribution_rates_to_use;
    printf("---- Step 5: params: %f\n", parameter);
    for (int k = 0; k < no_of_sensors; k++)
    {
        for (int j = 0; j <= k; j++)
        {
            sum += contribution_rate[j];
        }

        if (sum <= parameter)
        {
            no_of_contribution_rates_to_use = k - 1;
            printf("k:%d no_of_contribution_rates_to_use: %d\n", k, no_of_contribution_rates_to_use);
            return no_of_contribution_rates_to_use;
        }
    }

    printf("no_of_contribution_rates_to_use:%d\n", no_of_sensors);
    return no_of_sensors;
}

double **calculate_principal_components(double *sd_matrix, int no_of_sensors, double **eigen_vector, int no_of_contribution_rates_to_use)
{
    if (sd_matrix == NULL || eigen_vector == NULL || no_of_sensors == 0 || no_of_contribution_rates_to_use == 0)
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    int n = no_of_sensors;
    int m = no_of_contribution_rates_to_use;
    int count = 0;
    double **arrptr = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        arrptr[i] = (double *)malloc(n * sizeof(double));
    }
    if (arrptr == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arrptr[i][j] = sd_matrix[count];
            count++;
        }
    }
    double **principal_components_matrix = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        principal_components_matrix[i] = (double *)malloc(n * sizeof(double));
    }
    if (principal_components_matrix == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }

    printf("----- Step 3 -----\n");
    printf("== Principle component matrix:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            principal_components_matrix[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                principal_components_matrix[i][j] += eigen_vector[i][k] * arrptr[k][j];
                printf("%f ", principal_components_matrix[i][j]);
            }
            printf("\n");
        }
    }
    for(int i=0; i< no_of_sensors; i++){
        free(arrptr[i]);
    }
    free(arrptr);
    return principal_components_matrix;
}

double *calculate_integrated_support_degree_matrix(double **principle_components,
                                                   double *contribution_rate, int no_of_contribution_rates_to_use,
                                                   int no_of_sensors)
{
    int n_contribute = no_of_contribution_rates_to_use;
    int n_sensors = no_of_sensors;

    if ((principle_components == NULL) || (contribution_rate == NULL) || (n_contribute == 0) || (n_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }

    double *arr = (double *)malloc(n_sensors * sizeof(double));
    if (arr == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }

    /* Calculate integrated support degree score */
    printf("---- Step 6 -----\n");
    printf("= Integrated Support Degree Score: \n");
    for (int i = 0; i < n_sensors; i++)
    {
        for (int j = 0; j < n_contribute; j++)
        {
            arr[i] += principle_components[j][i] * contribution_rate[j];
            printf("%f ", arr[i]);
        }
    }
    printf("\n");

    return arr;
}

int eliminate_incorrect_data(double *integrate_support_degree_matrix,
                             double fault_tolerance, int no_of_sensors)
{
    int i, n_sensors = no_of_sensors;
    double mean_z = 0;
    double sum = 0;
    double *arr = integrate_support_degree_matrix;

    if ((arr == NULL) || (n_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return -1;
    }

    for (i = 0; i < n_sensors; i++)
    {
        sum += arr[i];
    }

    mean_z = sum / (i + 1);

    printf("--- Step 7 ---\n");
    printf("eliminate_incorrect_data: \n");
    for (int i = 0; i < n_sensors; i++)
    {
        if (fabs(arr[i]) < fabs(fault_tolerance * mean_z))
        {
            arr[i] = 0;
        }
        printf("%f ", arr[i]);
    }
    printf("\n");

    return 0;
}

double *calculate_weight_coefficient(double *integrate_support_degree_matrix,
                                     int no_of_sensors)
{
    int n_sensors = no_of_sensors;
    double *integrate_matrix = integrate_support_degree_matrix;
    double sum = 0;

    if ((integrate_matrix == NULL) || (n_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }

    double *arr = (double *)malloc(n_sensors * sizeof(double));
    if (arr == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return NULL;
    }

    memset(arr, 0, n_sensors * sizeof(double));

    for (int i = 0; i < n_sensors; i++)
    {
        sum += integrate_matrix[i];
    }

    printf("--- Step 8 ---\n");
    printf("weight_coefficient: \n");
    for (int i = 0; i < n_sensors; i++)
    {
        arr[i] = integrate_matrix[i] / sum;
        printf("%f ", arr[i]);
    }
    printf("\n");

    return arr;
}

double calculate_fused_output(double *weight_coefficient, double *sensor_data,
                           int no_of_sensors, double *fused_value)
{
    int n_sensors = no_of_sensors;

    if ((weight_coefficient == NULL) || (n_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return -1;
    }

    for (int i = 0; i < n_sensors; i++)
    {
        *fused_value += weight_coefficient[i] * sensor_data[i];
    }

    return 0;
}
