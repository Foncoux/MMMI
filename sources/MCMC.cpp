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
#include <algorithm>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_machine.h>
#include <gsl/gsl_sf_log.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/optimisation_algo.hpp"
#include "../headers/fonction_obj.hpp"

#include "../headers/fonction_discret.hpp"
#include "../headers/MCMC.hpp"

std::array<parametres,NB_CLASSE_AGE> MCMC(std::array<parametres,NB_CLASSE_AGE> cond_init,gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data)
{
    std::array<parametres,NB_CLASSE_AGE> p = cond_init;
    
    return metropolis_hastings(p,f,data,random_ptr);

}

std::array<parametres,NB_CLASSE_AGE> metropolis_hastings(std::array<parametres,NB_CLASSE_AGE> cond_init,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,gsl_rng* r)
{
    double sigma=SIGMA;
    double L_old;
    double L_new;
    double alpha;
    std::array<parametres,NB_CLASSE_AGE> p_old;
    std::array<parametres,NB_CLASSE_AGE> p_new;
    double nombre_acceptation = 0;
    double taux_acceptation = 0;
    std::string savename;

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        set_condition_initiale(f[classe],cond_init[classe].x0,classe);
    }

    while (bb_discret(f,cond_init,data) !=0)
    {
        std::cout << "param_out" << std::endl;
        cond_init = set_parametres_random(r);
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            set_condition_initiale(f[classe],cond_init[classe].x0,classe);
        }
    }

    
    p_old =  cond_init;
    L_old = fonction_obj(data,f,1);
    
    int j=0;
    int iter_select = 0;
    int i=0;
    bool stop = false; 
    while(stop == false)
    {
        
        //std::cout << i << std::endl;
        p_new = set_parametres_random_normal(r,sigma,p_old);
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            set_condition_initiale(f[classe],p_new[classe].x0,classe);
        }        

        if (bb_discret(f,p_new,data) == 0)
        {
            L_new = fonction_obj(data,f,1);

            alpha = gsl_rng_uniform(r);

            if (gsl_sf_log(alpha) < L_new - L_old)
            {   
                
                p_old = p_new;
                L_old = L_new;

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
                    bb_discret(f,p_old,data);
                    savename = DATA_MCMC_WRITE + std::to_string(j);
                    write_data(f,savename);

                    j++;
                    if (j >= NB_POST_DIST)
                    {
                        stop = true;
                        
                    }
                    std::cout << i << "  " << j << "  " << taux_acceptation << "  " << L_old << std::endl;
                }
                
            }else
            {
                std::cout << i << "  " << j << "  " << taux_acceptation << "  " << L_old << std::endl;
            }
            iter_select++;
        }else
        {
            i--;
        }     

        
        i++;
    }
    
    return p_old;

}