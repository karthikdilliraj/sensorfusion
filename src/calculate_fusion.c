#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "calculate_fusion.h"

struct support_degree_matrix calculate_support_degree_matrix(void)
{
    // if (node == NULL)
    // {
    //     printf("%s: Incorrect Input\n", __func__);
    //     return;
    // }
    // int i = 0;
    // while (node != NULL)
    // {
    //     printf("%c\n", node->sensor_name);
    //     node = node->next;
    //     i++;
    //     printf("%d\n", i);
    // }
    float values[] = {10, 0};
    struct support_degree_matrix spd;
    int length = sizeof(values) / sizeof(values[0]);
    spd.no_of_sensors = length;
    double **arrptr = (double **)malloc(length * sizeof(double *));
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        arrptr[i] = (double *)malloc(length * sizeof(double));
    }
    if (arrptr == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return;
    }
    spd.sd_matrix = (double *)malloc(sizeof(double) * length * length);

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            arrptr[i][j] = exp(-1 * fabs(values[i] - values[j]));
            spd.sd_matrix[count] = arrptr[i][j];
            count++;
        }
    }
    printf("Support Degree Matrix\n");
    for (int i = 0; i < length * length; i++)
    {
        printf("%f\n", spd.sd_matrix[i]);
    }
    free(arrptr);
    return spd;
}

struct eigen_systems calculate_eigensystem(struct support_degree_matrix spd)
{
    if ((spd.sd_matrix == NULL) || (spd.no_of_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return;
    }
    int length = spd.no_of_sensors;
    struct eigen_systems eigen;
    eigen.eigen_value = (double *)malloc(sizeof(double) * length);
    eigen.eigen_vector = (double **)malloc(length * sizeof(double *));
    for (int i = 0; i < length; i++)
    {
        eigen.eigen_vector[i] = (double *)malloc(length * sizeof(double));
    }
    if (eigen.eigen_vector == NULL || eigen.eigen_value == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return;
    }
    gsl_matrix_view m = gsl_matrix_view_array(spd.sd_matrix, length, length);

    gsl_vector *eval = gsl_vector_alloc(length);
    gsl_matrix *evec = gsl_matrix_alloc(length, length);

    gsl_eigen_symmv_workspace *w =
        gsl_eigen_symmv_alloc(length);

    gsl_eigen_symmv(&m.matrix, eval, evec, w);

    gsl_eigen_symmv_free(w);

    gsl_eigen_symmv_sort(eval, evec,
                         GSL_EIGEN_SORT_VAL_DESC);

    {
        int i;

        for (i = 0; i < length; i++)
        {
            eigen.eigen_value[i] = gsl_vector_get(eval, i);
            gsl_vector_view evec_i = gsl_matrix_column(evec, i);
            for (int j = 0; j < length; j++)
            {
                eigen.eigen_vector[i][j] = *(*(&evec_i.vector.data) + j * length);
            }
        }
    }

    for (int i = 0; i < length; i++)
    {
        printf("eigenvalue = %g\n", eigen.eigen_value[i]);
        printf("eigenvector = \n");
        for (int j = 0; j < length; j++)
        {
            printf("%g\n", eigen.eigen_vector[i][j]);
        }
    }
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    return eigen;
}

double *calculate_contribution_rate(struct eigen_systems eigen, int no_of_sensors)
{
    if ((eigen.eigen_value == NULL) || (eigen.eigen_vector == NULL) || (no_of_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    int length = no_of_sensors;
    double *contribution_rate = (double *)malloc(length * sizeof(double));
    if (contribution_rate == NULL)
    {
        printf("%s: Unable to allocate memory!\n", __func__);
        return;
    }
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += eigen.eigen_value[i];
    }
    printf("Contribution rate\n");
    for (int j = 0; j < length; j++)
    {
        contribution_rate[j] = eigen.eigen_value[j] / sum;
        printf("%g\n", contribution_rate[j]);
    }
    return contribution_rate;
}

int determine_contribution_rates_to_use(double *contribution_rate, float parameter, int no_of_sensors)
{
    if ((contribution_rate == NULL) || (parameter == 0) || (no_of_sensors == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    int length = no_of_sensors;
    double sum = 0;
    int m;
    for (int k = 0; k < length; k++)
    {
        for (int j = 0; j <= k; j++)
        {
            sum += contribution_rate[j];
        }

        if (sum <= parameter)
        {
            m = k - 1;
            printf("Number of Contribution rates to use %d\n", m);
            return m;
        }
    }
    printf("Number of Contribution rates to use %d\n", length);
    return length;
}

double **calculate_principal_components(struct support_degree_matrix spd, double **eigen_vector, int no_of_contribution_rates_to_use)
{
    if ((spd.sd_matrix == NULL) || (eigen_vector == NULL) || (spd.no_of_sensors == 0) || (no_of_contribution_rates_to_use == 0))
    {
        printf("%s: Incorrect Input\n", __func__);
        return NULL;
    }
    int n = spd.no_of_sensors;
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
        return;
    }
    printf("Support Degree Matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arrptr[i][j] = spd.sd_matrix[count];
            printf("%f\n", arrptr[i][j]);
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
        return;
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            principal_components_matrix[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                principal_components_matrix[i][j] += eigen_vector[i][k] * arrptr[k][j];
            }
        }
    }
    printf("Principal components of D matrix, row:%d, col:%d\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f\n", principal_components_matrix[i][j]);
        }
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
    for (int i = 0; i < n_sensors; i++)
    {
        for (int j = 0; j < n_contribute; j++)
        {
            printf("sensors: %d-%f, contri: %d-%f\n", i, principle_components[i][j], j, contribution_rate[i]);
            arr[i] += principle_components[i][j] * contribution_rate[i];
        }
    }

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

    for (int i = 0; i < n_sensors; i++)
    {
        if (fabs(arr[i]) < fabs(fault_tolerance * mean_z))
        {
            arr[i] = 0;
        }
    }

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

    for (int i = 0; i < n_sensors; i++)
    {
        arr[i] = integrate_matrix[i] / sum;
    }

    return arr;
}

double calculate_fused_output(double *weight_cofficienet, double *sensor_data,
                              int no_of_sensors)
{
    double fused_value = 0;
    int n_sensors = no_of_sensors;

    for (int i = 0; i < n_sensors; i++)
    {
        fused_value += weight_cofficienet[i] * sensor_data[i];
    }

    return fused_value;
}
