#include <array>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>
#include <string>
#include <time.h>

#include "config/config.hpp"

#include "fonction_discret.hpp"
#include "Data.hpp"

#include "Nomad_file.hpp"
#include "optimisation_algo.hpp"



int main (int argc, char* argv[])
{   
    
    COND_INIT_NBR = stoi(argv[1]);
    (void) argc;

    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires
    gsl_rng_set(random_ptr,time(NULL));
    int test = NOMAD_ALGO;
    config_table_extern();

    
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> param_opti;

    if(test == 0){

        ODE f(0);
        std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init;
       
        if (READ_SAVE_PARAM)
        {
            cond_init = read_save_parameters(SAVE_TO_READ);
        }else
        {
            cond_init = set_cond_init_mcmc(COND_INIT_NBR,COND_INIT_filename);
            //cond_init = set_parametres_random(random_ptr);
        }
        
        param_opti = optimisation_algo_choice(random_ptr, f, cond_init);

        model(f,param_opti);
        
        if (WRITE_SAVE_PARAM == true)
        {
            write_save_parameters(param_opti,SAVE_TO_WRITE); 
        }
        
        //write_data_csv(f,DATA_TO_WRITE); 
        
        //print_parameter(param_opti);


    }else{
        
        main2();

        ODE f(0);
        param_opti = read_nomad_best_feasible_solution();

        //param_opti = optimisation_algo_choice(random_ptr, f, param_opti);

        model(f,param_opti);
        
        write_save_parameters(param_opti,SAVE_TO_WRITE2);
        write_data_csv(f,DATA_TO_WRITE); 
      


    }

    gsl_rng_free(random_ptr);


    return 0;

}

