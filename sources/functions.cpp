#include "../headers/functions.hpp"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>


int oscillateur_harm(double t, const double y[], double f[],void *params)
{
    (void)(t); /* avoid unused parameter warning */
    (void)(params);
    f[0] = y[1];
    f[1] = -y[0];

    return GSL_SUCCESS;

}

int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    (void)(t); /* avoid unused parameter warning */
    (void)(params);
    (void)(y);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix * m = &dfdy_mat.matrix;
    gsl_matrix_set (m, 0, 0, 0.0); //valeur de l'élément (0,0) de la jacobienne
    gsl_matrix_set (m, 0, 1, 1.0);//valeur de l'élément (0,1) de la jacobienne
    gsl_matrix_set (m, 1, 0, - 1.0); //valeur de l'élément (1,0) de la jacobienne
    gsl_matrix_set (m, 1, 1, 0.0); //valeur de l'élément (1,1) de la jacobienne

    dfdt[0] = 0.0; // valeur de la dérivée de l'équation 1 par rapport à t
    dfdt[1] = 0.0; // valeur de la dérivée de l'équation 2 par rapport à t
    return GSL_SUCCESS;
}