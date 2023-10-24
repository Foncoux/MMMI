#include <array>
#include <vector>
#include <iostream>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>
#include <string>

#include "config/config.hpp"
#include "headers/Data.hpp"
#include "headers/Parametres.hpp"
#include "headers/ODE.hpp"
#include "headers/read_and_write_data.hpp"
#include "headers/optimisation_algo.hpp"
#include "headers/MCMC.hpp"
#include "headers/fonction_discret.hpp"
#include "headers/fonction_continuous.hpp"



int main (void)
{   
    config_table_extern();
    int fct_obj_choice = FCT_OBJ_CHOICE;
    Data data;
    std::array<ODE,NB_CLASSE_AGE> f;
    std::array<parametres,NB_CLASSE_AGE> param_opti;
    std::array<parametres,NB_CLASSE_AGE> cond_init;
    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires

    if (READ_SAVE_PARAM)
    {
        cond_init = read_save_parameters(SAVE_TO_READ);
    }else
    {
        cond_init = set_parametres_random(random_ptr);
    }
    
    param_opti = optimisation_algo_choice(random_ptr, f, data, fct_obj_choice, cond_init);

    model(f,param_opti,data);
    
    if (WRITE_SAVE_PARAM == true)
    {
        write_save_parameters(param_opti,SAVE_TO_WRITE); 
    }
    
    write_data(f,DATA_TO_WRITE); 
    
    //print_parameter(param_opti);

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