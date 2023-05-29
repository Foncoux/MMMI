
#include "headers/blackbox.hpp"
#include "headers/read_and_write_data.hpp"
#include "headers/functions.hpp"
#include "headers/integration.hpp"
#include "headers/fonction_discret.hpp"
#include <array>
#include <iostream>

#include <gsl/gsl_sf_log.h>



int main (void)
{   
    Data data;

    set_social_contact_matrix(data.social_constact_matrix);

    read_data_day("../data/day_data.csv", data.day_all);

    read_data_week_age("../data/hosp_week_age.csv",data.week_hosp_ages);   

    read_data_month_age("../data/death_month_age.csv",data.month_death_ages);


    for (size_t i = 0; i < NB_DATA_DAY; i++)
    {
        for (size_t j = 0; j < NB_DAY; j++)
        {
            std::cout << data.day_all[i][j] << " ";
        }
        std::cout << std::endl;
        
    }


    
    time_t seed = time(NULL);
    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires
    gsl_rng_set(random_ptr, seed);


    


    ODE f[NB_CLASSE_AGE] = {3};
  

    
    parametres param_opti = random_search_radius(random_ptr,f,data);
    //parametres param_opti = random_search(random_ptr,f,data);


    
    if(DISCRET == 0){

    }else if(DISCRET == 1)
    {
        set_condition_initiale(f,param_opti.x0);
        bb_discret(f,param_opti);
    }
    
    
    write_data(f[0].m_result_integration); 
    
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