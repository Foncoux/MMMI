#include <array>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>
#include <iomanip>
#include <iostream>


#include "config/config.hpp"

#include "fonction_discret.hpp"
#include "Data.hpp"

#include "Nomad_file.hpp"
#include "optimisation_algo.hpp"

int main (int argc, char* argv[])
{   
    COND_INIT_NBR = stoi(argv[1]);
    (void) argc;

    
    STAT_nbr_model_evaluation = 0;
    STAT_nbr_model_evaluation_aborted = 0;
    STAT_obj_fct_value = 2000000000.0;


 
    gsl_rng* random_ptr = gsl_rng_alloc(gsl_rng_mt19937);// Initialiser le générateur de nombres aléatoires
    gsl_rng_set(random_ptr,time(NULL));
    
    int test = NOMAD_ALGO;
    config_table_extern();

    
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> param_opti;

   
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &STAT_CPU_time_start);
    STAT_time_start = chrono::high_resolution_clock::now();

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


    STAT_time_end = chrono::high_resolution_clock::now();
    // Calculating total time taken by the program.
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(STAT_time_end - STAT_time_start).count();
    
    // Stop measuring time and calculate the elapsed time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &STAT_CPU_time_end);
    long seconds = STAT_CPU_time_end.tv_sec - STAT_CPU_time_start.tv_sec;
    long nanoseconds = STAT_CPU_time_end.tv_nsec - STAT_CPU_time_start.tv_nsec;
    double time_taken_CPU = seconds + nanoseconds*1e-9;
 
    gsl_rng_free(random_ptr);

    time_taken *= 1e-9;
    std::cout << "Time taken by program is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " sec" << std::endl;

    // Calculating total time taken by the program.
    cout << "Time taken (CPU) by program is : " << fixed 
         << time_taken_CPU << setprecision(9);
    cout << " sec " << endl;


    return 0;

}

