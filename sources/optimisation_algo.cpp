#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_machine.h>
#include <gsl/gsl_sf_log.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_obj.hpp"
#include "../headers/fonction_discret.hpp"
#include "../headers/optimisation_algo.hpp"
#include "../headers/MCMC.hpp"
#include "../headers/fonction_continuous.hpp"


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> optimisation_algo_choice(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,Data data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init)
{   
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> param_opti;
    switch (ALGO)
    {
    case 1:
        param_opti = random_search(random_ptr,f,data,fct_obj_choice,cond_init);
        break;

    case 2:

        break;  
    case 3:
        param_opti = MCMC(cond_init,random_ptr,f,data);
        break; 
    case 4:
        param_opti = random_search_normal(random_ptr,f,data,fct_obj_choice,cond_init);
        break;
    default:
        std::cout << "mauvais choix d'algo" <<   std::endl;
        exit(0);
        break;
    }
    return param_opti;
}


/**
 * @brief effectue l'algorithme de recherche aléatoire
 * 
 * @param random_ptr pointeur pour l'aléatoire
 * @param f tableau de fonction discrete. Modifiée en sortie de fonction.
 * @param data données réelles pour la calibration.
 * @param fct_obj_choice entier 0 ou 1 permettant de choisir les moindres carrés ou le -log likelyhood. moindres carrés non-fonctionnel pour plusieurs classe d'age
 * @param cond_init parametres initiaux pour le modèle
 * @return std::array<parametres,NB_CLASSE_AGE> tableau de parametres contenant les parametres optimaux par classe d'age, trouvé par l'algo
 */
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> random_search(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init)
{
    
    double y[COMPARTIMENT*NB_CLASSE_AGE];
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    int output_model_return;
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> param_opti = cond_init;

    while (model(f,param_opti,data) != 0)
    {
        param_opti = set_parametres_random(random_ptr);
    }
    
    
    double fct_obj = -fonction_obj(data,f,fct_obj_choice); ///////
    
    for (size_t i = 0; i < NB_ITE_BLACKBOX; i++)
    {   
                
        p = set_parametres_random(random_ptr);
        
        std::cout << i << "   ";
            
        if (model(f,p,data)  == 0)
        {
            if(minimisation(fct_obj, data, f,fct_obj_choice))
            {
                param_opti = p;
            }
        }
    
        
        std::cout << std::endl;
    }

    std::cout << fct_obj << std::endl;

    return param_opti;
  
}




/**
 * @brief effectue l'algorithme de recherche aléatoire avec un rayon de recherche dégressif au fur et à mesure des itérations, autour du dernier points optimal, 
 * 
 * @param random_ptr pointeur pour l'aléatoire
 * @param f tableau de fonction discrete. Modifiée en sortie de fonction.
 * @param data données réelles pour la calibration.
 * @param fct_obj_choice entier 0 ou 1 permettant de choisir les moindres carrés ou le -log likelyhood. moindres carrés non-fonctionnel pour plusieurs classe d'age
 * @param cond_init parametres initiaux pour le modèle
 * @return std::array<parametres,NB_CLASSE_AGE> tableau de parametres contenant les parametres optimaux par classe d'age, trouvé par l'algo
 */
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> random_search_normal(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init)
{
    double sigma=SIGMA;
    int save_intermediaire = 0;
    double accept_ite = 0;    
    double y[COMPARTIMENT*NB_CLASSE_AGE];

    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> param_opti = cond_init;
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    
    while (model(f,param_opti,data) !=0)
    {
        param_opti = set_parametres_random(random_ptr);
    }
    double fct_obj = -fonction_obj(data,f,fct_obj_choice); ///////

    for (size_t i = 0; i < NB_ITE_BLACKBOX; i++)
    {   
        if(i==NB_ITE_BLACKBOX-2)
        {
            i=0;
            accept_ite = 0;
            sigma = sigma/2;
        }

        if(sigma < STOP_ALGO){break;}        

        p = set_parametres_random_normal(random_ptr,sigma,param_opti);
        
        std::cout << i << "   " << sigma << "   ";    
        if (model(f,p,data) == 0)
        {
            if(minimisation(fct_obj, data, f,fct_obj_choice))
            {
                i=0;
                accept_ite++;
                param_opti = p;
            }
        }else{i--;}

        std::cout << std::endl;
    }

    std::cout << fct_obj << accept_ite << std::endl;

    return param_opti;
  
}




/**
 * @brief gère la verification du minimum
 * 
 * @param fct_obj fonction objectif actuelle. Modifié à la sortie
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @param fct_obj_choice 1 si utilisation du log likelyhood, 0 sinon
 * @return true s'il le jeu de parametres minimise
 * @return false sinon
 */
bool minimisation(double &fct_obj, const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data,int fct_obj_choice)
{
    double fct_obj_temp = -fonction_obj(data, output_data,fct_obj_choice);
    
    std::cout << fct_obj << "  |  " << fct_obj_temp;

    if(fct_obj_temp < fct_obj)
    {
        fct_obj = fct_obj_temp;
        
        return true;
    }

    return false;
    
}