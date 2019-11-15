#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "calculate_fusion.h"

double *calculate_support_degree_matrix (void){
    float values[] = {10, 6};
    double *d_array;
    int length = sizeof(values) / sizeof(values[0]);
    double **arrptr = (double **)malloc(length * sizeof(double *));
    for (int i = 0; i < length; i++)
    {
        arrptr[i] = (double *)malloc(length * sizeof(double));
    }
    d_array = (double *)malloc(sizeof(double) * length * length);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            arrptr[i][j] = exp(-1 * fabs(values[i] - values[j]));
            d_array[i + j] = arrptr[i][j];
        }
    }
    printf("Support Degree Matrix\n");
    for(int i =0;i<length*length;i++){
        printf("%f\n",d_array[i]);
    }
    return d_array;
}

void calculate_eigensystem (double *support_degree_matrix){
    int length = 2;
    gsl_matrix_view m = gsl_matrix_view_array(support_degree_matrix, length, length);

    gsl_vector *eval = gsl_vector_alloc(length);
    gsl_matrix *evec = gsl_matrix_alloc(length, length);

    gsl_eigen_symmv_workspace *w =
        gsl_eigen_symmv_alloc(length);

    gsl_eigen_symmv(&m.matrix, eval, evec, w);

    gsl_eigen_symmv_free(w);

    gsl_eigen_symmv_sort(eval, evec,
                         GSL_EIGEN_SORT_ABS_ASC);

    {
        int i;

        for (i = 0; i < length; i++)
        {
            double eval_i = gsl_vector_get(eval, i);
            gsl_vector_view evec_i = gsl_matrix_column(evec, i);

            printf("eigenvalue = %g\n", eval_i);
            printf("eigenvector = \n");
            gsl_vector_fprintf(stdout,
                               &evec_i.vector, "%g");
        }
    }

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    return;
}

