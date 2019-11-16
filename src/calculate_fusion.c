#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "calculate_fusion.h"

struct support_degree_matrix calculate_support_degree_matrix(void)
{
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
    int length = spd.no_of_sensors;
    struct eigen_systems eigen;
    eigen.eigen_value = (double *)malloc(sizeof(double) * length);
    eigen.eigen_vector = (double **)malloc(length * sizeof(double *));
    for (int i = 0; i < length; i++)
    {
        eigen.eigen_vector[i] = (double *)malloc(length * sizeof(double));
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
    int length = no_of_sensors;
    double *contribution_rate = (double *)malloc(length * sizeof(double));
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
    int length = no_of_sensors;
    double sum = 0;
    int m;
    for (int k = 0; k < length; k++)
    {
        sum += contribution_rate[k];
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
    int n = spd.no_of_sensors;
    int m = no_of_contribution_rates_to_use;
    int count = 0;
    double **arrptr = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        arrptr[i] = (double *)malloc(n * sizeof(double));
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
    printf("Principal components of D matrix\n");
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
