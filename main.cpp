
#include <iostream>
#include <array>
#include "integrator.hpp"
#include "../headers/functions.hpp"

#include "config/config.hpp"
#include "ODE.hpp"

#include "../headers/read_data.hpp"
#include "../headers/fonction_obj.hpp"

#include "../headers/blackbox.hpp"


int main (void)
{   
    time_t seed = time(NULL);
    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires
    gsl_rng_set(random_ptr, seed);

        
    double y[COMPARTIMENT] = { 1 - 1/POP_TOT,1/POP_TOT,0,0,0};
    

    //double y[COMPARTIMENT] = { 1,0};

    ODE f(2,y);
    parametres param_opti;

    param_opti.beta = 2.5;
    param_opti.delta = 0.4; // Générer un nombre aléatoire compris entre 0 et 1
    param_opti.gamma = 0.4;
    param_opti.eps = 0.4;
    param_opti.r = 0.4;
    
        
   

    parametres p = set_parametres(random_ptr,param_opti);
    param_opti = p;
    
    integrate(f,p,y);
    

    std::array<double,DEATH_NB_DAY> death;
    read_dataD(death);

    std::array<double,HOSP_NB_DAY> hosp;
    read_dataH(hosp);


    for (int i = 0; i < DEATH_NB_DAY; i++)
    {
        std::cout << death[i]*POP_TOT << " ";
    }
    std::cout << "\n \n" << death.size() << " ";


    double fct_obj = min_log_likelyhood_death(death, f.m_result_integration) + min_log_likelyhood_hosp(hosp, f.m_result_integration);;

    for (size_t i = 0; i < 200000; i++)
    {   
        y[0] = 1 - 1/POP_TOT;
        y[1] = 1/POP_TOT;
        y[2] = 0;
        y[3] = 0;
        y[4] = 0;
        
        //y = { 1 - 10/POP_TOT,10/POP_TOT,0,0,0};
        
        parametres p = set_parametres(random_ptr,param_opti);

        integrate(f,p,y);

        std::cout << i << "   " << "\n";

        if(minimisation(fct_obj, death, hosp, f.m_result_integration))
        {
            param_opti = p;
        }
    }

    y[0] = 1 - 1/POP_TOT;
    y[1] = 1/POP_TOT;
    y[2] = 0;
    y[3] = 0;
    y[4] = 0;

    std::cout << fct_obj << std::endl;

    integrate(f,param_opti,y);

    write_data(f.m_result_integration);   
    //double y[COMPARTIMENT] = { 1 - 10/POP_TOT,10/POP_TOT,0,0,0};

    gsl_rng_free(random_ptr);

    return 0;
}


/*
for (int i = 0; i < DEATH_NB_DAY; i++)
    {
        std::cout << death[i] << std::endl;
    }
*/
/*
int main (void)
{
const gsl_odeiv2_step_type * T = gsl_odeiv2_step_rk8pd;
gsl_odeiv2_step * s = gsl_odeiv2_step_alloc (T, 2);
gsl_odeiv2_control * c = gsl_odeiv2_control_y_new (1e-6, 0.0);
gsl_odeiv2_evolve * e = gsl_odeiv2_evolve_alloc (2);
double mu = 10;
gsl_odeiv2_system sys = {func, jac, 2, &mu};
double t = 0.0, t1 = 100.0;
double h = 1e-6;
double y[2] = { 1.0, 0.0 };
while (t < t1)
{
    int status = gsl_odeiv2_evolve_apply (e, c, s,
    &sys,
    &t, t1,
    &h, y);
    if (status != GSL_SUCCESS)
    {
        break;
    }
    printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
}
gsl_odeiv2_evolve_free (e);
gsl_odeiv2_control_free (c);
gsl_odeiv2_step_free (s);
return 0;
}

*/