
#include "headers/blackbox.hpp"
#include "headers/read_and_write_data.hpp"
#include "headers/functions.hpp"
#include "headers/integration.hpp"
#include "headers/fonction_discret.hpp"
#include <array>

#include <gsl/gsl_sf_log.h>



int main (void)
{   
   
    time_t seed = time(NULL);
    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires
    gsl_rng_set(random_ptr, seed);


    std::array<std::array<std::array<double, T_FINAL>, COMPARTIMENT>, NB_CLASSE_AGE> model_result;


    ODE f[NB_CLASSE_AGE] = {3};
    
    
    std::array<double,DEATH_NB_DAY> death;
    read_dataD(death);
    std::array<double,HOSP_NB_DAY> hosp;
    read_dataH(hosp);

    

    
    parametres param_opti = random_search_radius(random_ptr,f,death,hosp,model_result);

    
    if(DISCRET == 0){
    /*  double y[COMPARTIMENT];
        std::copy(std::begin(param_opti.x0), std::end(param_opti.x0), std::begin(y));
        
        f.set_condition_initiale(y);

        integrate(f,param_opti,y);
    */
    }else if(DISCRET == 1)
    {
        for (size_t i = 0; i < NB_CLASSE_AGE; i++)
        {
            f[i].set_condition_initiale(param_opti.x0);
        }

        bb_discret(f,param_opti);
    }

    write_data(f[0].m_result_integration); 
    
    /*
    for (size_t i = 0; i < T_FINAL; i++)
    {
        std::cout << f.m_result_integration[0][i] * POP_TOT << " ";
    }
    */
    

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