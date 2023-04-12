
#include "../headers/integrator.hpp"
#include "../headers/functions.hpp"
#include "../config/config.hpp"



void integrate(ODE &f,parametres p, double y[])
{
    
    gsl_odeiv2_system sys = {f.m_function, f.m_jacobian, 5, &p};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);

    

    double t = T_DEBUT;


    for (int i = 1; i < T_FINAL; i++)
    {
        double ti = i * (double)T_FINAL / (double)T_FINAL;
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        //printf ("%.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4]);

        

        if (status != GSL_SUCCESS)
        {
            printf ("error, return value=%d\n", status);
            break;
        }

        

        f.m_result_integration[0][i] = y[0];
        f.m_result_integration[1][i] = y[1];
        f.m_result_integration[2][i] = y[2];
        f.m_result_integration[3][i] = y[3];
        f.m_result_integration[4][i] = y[4];

       

    }
    //std::cout << f.m_result_integration[0][127] << std::endl;
    //printf ("%.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4]);
    //std::cout << f.m_result_integration[1][153] << std::endl;

    gsl_odeiv2_driver_free (d);
}