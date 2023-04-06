
#include "../headers/integrator.hpp"
#include "../headers/functions.hpp"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

void integrate(ODE f)
{
    parametres p = {10};
    
    gsl_odeiv2_system sys = {f.m_function, jacobian_osc, 2, &p};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45,
    1e-6, 1e-6, 0.0);
    int i;
    double t = 0.0, t1 = 100.0;
    double y[2] = { 1.0, 0.0 };
    for (i = 1; i <= 100; i++)
    {
        double ti = i * t1 / 100.0;
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
    if (status != GSL_SUCCESS)
    {
        printf ("error, return value=%d\n", status);
        break;
    }
    
    }
    gsl_odeiv2_driver_free (d);
}