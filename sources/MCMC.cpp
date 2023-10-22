/**
 * @file MCMC.cpp
 * @author Esteban Foncoux
 * @brief gere la partie MCMC
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <array>
#include <vector>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_machine.h>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_sf_exp.h>


#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/optimisation_algo.hpp"
#include "../headers/fonction_obj.hpp"

#include "../headers/fonction_discret.hpp"
#include "../headers/MCMC.hpp"
#include "../headers/fonction_continuous.hpp"

std::array<parametres,NB_CLASSE_AGE> MCMC(std::array<parametres,NB_CLASSE_AGE> cond_init,gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data)
{
    std::array<parametres,NB_CLASSE_AGE> p = cond_init;
    
    return metropolis(p,f,data,random_ptr);

}

std::array<parametres,NB_CLASSE_AGE> metropolis(std::array<parametres,NB_CLASSE_AGE> cond_init,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,gsl_rng* r)
{
    double sigma=SIGMA;
    double L_old, LL_old;
    double L_new, LL_new;
    double alpha;
    std::array<parametres,NB_CLASSE_AGE> p_old;
    std::array<parametres,NB_CLASSE_AGE> p_new;
    double nombre_acceptation = 0;
    double taux_acceptation = 0;
    std::string savename;

    while (model(f,cond_init,data) !=0)
    {
        cond_init = set_parametres_random(r);
    }
    
    p_old = cond_init;
    LL_old = fonction_obj(data,f,1);
    
    int j=0;
    int iter_select = 0;
    int i=0;
    bool stop = false; 
    //std::cout << "ite_tot\t| " << "Nb_post_dist\t| " << "taux_acceptation\t| " << "LL_old\t\t| " << "\n";
    
    std::cout << std::left  << std::setw(10) << "ite_tot"
                            << std::setw(4) << "|"
                            << std::setw(15) << "Nb_post_dist"
                            << std::setw(4) << "|"
                            << std::setw(15) << "taux_accept"
                            << std::setw(4) << "|"
                            << std::setw(15) << "LL_old"
                            << std::setw(4) << "|"
                            << std::setw(15) << "LL_new - LL_old"
                            << "\r" << std::endl;

    while(stop == false)
    {
      
        p_new = set_parametres_random_normal(r,sigma,p_old);

        if (model(f,p_new,data) == 0)
        {
            LL_new = fonction_obj(data,f,1);
            alpha = gsl_rng_uniform(r);

            if (gsl_sf_log(alpha) < LL_new - LL_old)
            {   
                p_old = p_new;
                LL_old = LL_new;
                if( i > BURNIN_STEP ){
                    nombre_acceptation++;
                }
            }


            if( i > BURNIN_STEP )
            {
                taux_acceptation = nombre_acceptation/(i-BURNIN_STEP+1);
                if (iter_select > ITE_RECUP_MCMC)
                {
                    iter_select=0;
                    savename = SAVE_MCMC_WRITE + std::to_string(j);
                    write_save_parameters(p_old,savename);
                    model(f,p_old,data);
                    savename = DATA_MCMC_WRITE + std::to_string(j);
                    write_data(f,savename);

                    j++;
                    if (j >= NB_POST_DIST)
                    {
                        stop = true;
                        
                    }
                    
                }
                
            }
            

            std::cout << std::left  << std::setw(10) << i
                                    << std::setw(4) << "|"
                                    << std::setw(15) << j
                                    << std::setw(4) << "|"
                                    << std::setw(15) << std::setprecision(10)<< taux_acceptation
                                    << std::setw(4) << "|"
                                    << std::setw(15) << std::fixed << std::setprecision(2) << LL_old
                                    << std::setw(4) << "|"
                                    << std::setw(15) << LL_new - LL_old
                                    << "\r" << std::flush;


            //std::cout << i << "\t| " << j << "\t\t| " << taux_acceptation << "\t\t\t| " << LL_old << "\t\t| "<< LL_new - LL_old <<" \t\r" << std::flush;

            iter_select++;
        }else
        {
            i--;
        }     
    
        
        i++;
    }
    
    std::cout << std::setprecision(16) << std::endl;
    return p_old;

}