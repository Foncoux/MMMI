#include <array>
#include <vector>
#include <iostream>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>
#include <string>

#include "config/config.hpp"
#include "headers/Parametres.hpp"
#include "headers/ODE.hpp"
#include "headers/read_and_write_data.hpp"
#include "headers/optimisation_algo.hpp"
#include "headers/MCMC.hpp"
#include "headers/fonction_discret.hpp"
#include "headers/fonction_continuous.hpp"

int main (void)
{   
 
/*
    Data data;
    set_social_contact_matrix(data.social_constact_matrix);

    ODE f[1] = {3};
    parametres p;
    p.beta[0] = 0.8;
    p.beta[1] = 0.5;
    p.beta[2] = 0.7;

    p.delta = 0.2;
    p.eps = 0.3;
    p.gamma = 0.2#include <vector>;
    p.r = 0.1;
    
    p.x0[0][I_COMP] = 3250/POP_TOT;
    p.x0[0][S_COMP] = 1-p.x0[0][I_COMP];
    p.x0[0][R_COMP] = 0;
    p.x0[0][Q_COMP] = 0;
    p.x0[0][D_COMP] = 0;

    set_condition_initiale(f,p.x0);
    bb_discret(f,p,data);
       
    write_data(f[0].m_result_integration); 
*/

    config_table_extern();
    int fct_obj_choice = FCT_OBJ_CHOICE;

    

    Data data;

    time_t seed = time(NULL);
    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires
    gsl_rng_set(random_ptr, seed);


    std::array<parametres,NB_CLASSE_AGE> cond_init;
    std::array<parametres,NB_CLASSE_AGE> param_opti;

    std::array<ODE,NB_CLASSE_AGE> f;


    std::string filename = SOCIAL_CONTACT_MATRIX_filename;
    set_social_contact_matrix(data.social_contact_matrix,filename);

    read_data_day(DAY_DATA_filename, data.day_all);

    if (NB_CLASSE_AGE != 1)
    {
        read_data_week_age(HOSP_WEEK_AGE_DATA_filename,data.week_hosp_ages);  
    }
    
     

    read_data_month_age(DEATH_MONTH_AGE_DATA_filename,data.month_death_ages);

    read_data_day(DAY_DEATH_AGE_DATA_filename, data.day_death_age);
    

    if (READ_SAVE_PARAM)
    {
        cond_init = read_save_parameters(SAVE_TO_READ);
    }else
    {
        cond_init = set_parametres_random(random_ptr);
    }
    


    switch (ALGO)
    {
    case 1:
        param_opti = random_search(random_ptr,f,data,fct_obj_choice,cond_init);
        break;

    case 2:
        param_opti = random_search_radius(random_ptr,f,data,fct_obj_choice,cond_init);
        break;  
    case 3:
        param_opti = MCMC(cond_init,random_ptr,f,data);
        break; 
    case 4:
        param_opti = random_search_normal(random_ptr,f,data,fct_obj_choice,cond_init);
        break;
    default:
        std::cout << "mauvais choix d'algo" <<   std::endl;
        return 0;
        break;
    }

    //std::cout << param_opti[0].x0[0][0] << std::endl;
    
    
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        set_condition_initiale(f[classe],param_opti[classe].x0,classe);
    }

    //bb_discret(f,param_opti,data);
    double y[COMPARTIMENT*NB_CLASSE_AGE];
        
    write_result_conversion_ODE_to_vector(f, y, 0);

    integrate(f,param_opti,y);

    //std::cout << f[0].m_result_integration[0][0] << std::endl;
    if (WRITE_SAVE_PARAM == true)
    {
        write_save_parameters(param_opti,SAVE_TO_WRITE); 
    }
    
    write_data(f,DATA_TO_WRITE); 
    

    print_parameter(param_opti);

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