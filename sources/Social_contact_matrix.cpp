#include <gsl/gsl_matrix.h>

void social_contact(gsl_matrix* mat)
{
    // Initialiser les valeurs de la matrice
    gsl_matrix_set(mat, 0, 0, 1.0);
    gsl_matrix_set(mat, 0, 1, 2.0);
    gsl_matrix_set(mat, 0, 2, 3.0);
    gsl_matrix_set(mat, 1, 0, 4.0);
    gsl_matrix_set(mat, 1, 1, 5.0);
    gsl_matrix_set(mat, 1, 2, 6.0);
}

