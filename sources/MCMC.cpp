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
#include <cmath>

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

std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> MCMC(std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init,gsl_rng* random_ptr,ODE& f,const Data &data)
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p = cond_init;
    
    double sigma = SIGMA;
    if(BURNIN_PHASE == true)
    {
        p = burning_phase(p,f,data,random_ptr,sigma);
    }
    if(MCMC_PHASE == true)
    {
        p = metropolis(p,f,data,random_ptr,sigma);

    }
    
    return p;

}

std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> burning_phase(std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init,ODE& f,const Data &data,gsl_rng* r,double &sigma)
{
    double LL_old;
    double LL_new;
    double alpha;
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_old;
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_new;
    double nombre_acceptation = 0;
    double taux_acceptation = 0;
    double sommeLL;
    int compteur_moyenne=1;
    int compteur_suiteLL=0;
    double moyenneLL_old=0,moyenneLL_new=0;
    std::string savename;
    double gamma = 0.9;

    while (model(f,cond_init,data) !=0)
    {
        cond_init = set_parametres_random(r);
    }
    
    p_old = cond_init;
    LL_old = fonction_obj(data,f,1);
    
    int j=0;
    int iter_select = 0;
    int iter_total=0;
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
                            << std::setw(4) << "|"
                            << std::setw(15) << "sigma"
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
                
                nombre_acceptation++;
                
            }
            



            taux_acceptation = nombre_acceptation/(iter_total+1);
            //sigma = sigma*gsl_sf_exp(gamma*((taux_acceptation-0.234)/(1-0.234)));
            sigma = sigma*gsl_sf_exp(gamma*((taux_acceptation-0.50)/(1-0.50)));

            std::cout << std::left  << std::setw(10) << iter_total
                                    << std::setw(4) << "|"
                                    << std::setw(15) << j
                                    << std::setw(4) << "|"
                                    << std::setw(15) << std::setprecision(10)<< taux_acceptation
                                    << std::setw(4) << "|"
                                    << std::setw(15) << std::fixed << std::setprecision(2) << LL_old
                                    << std::setw(4) << "|"
                                    << std::setw(15) << LL_new - LL_old
                                    << std::setw(4) << "|"
                                    << std::setw(15)<< std::setprecision(10) << sigma

                                    << "\r" << std::flush;
            

             
        }else
        {
            iter_total--;
        }     
        if(iter_total>BURNIN_STEP || compteur_suiteLL == 5)
        {
            stop=true;
        }
        
        iter_total++;
    }
    
    std::cout << std::setprecision(16) << std::endl;
    return p_old;

}


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> metropolis(std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init,ODE& f,const Data &data,gsl_rng* r,double &sigma)
{
    double LL_old,LL_new;
    double alpha;
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_old;
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_new;
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
    int iter_total=0;
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
                            << std::setw(4) << "|"
                            << std::setw(15) << "sigma"
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
                
                nombre_acceptation++;
                
            }


                  
            taux_acceptation = nombre_acceptation/(iter_total+1);
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
            
            std::cout << std::left  << std::setw(10) << iter_total
                                    << std::setw(4) << "|"
                                    << std::setw(15) << j
                                    << std::setw(4) << "|"
                                    << std::setw(15) << std::setprecision(10)<< taux_acceptation
                                    << std::setw(4) << "|"
                                    << std::setw(15) << std::fixed << std::setprecision(2) << LL_old
                                    << std::setw(4) << "|"
                                    << std::setw(15) << LL_new - LL_old
                                    << std::setw(4) << "|"
                                    << std::setw(15)<< std::setprecision(10) << sigma
                                    << "\r" << std::flush;

            iter_select++;
        }else
        {
            iter_total--;
        }     
    
        
        iter_total++;
    }
    
    std::cout << std::setprecision(16) << std::endl;
    return p_old;

}