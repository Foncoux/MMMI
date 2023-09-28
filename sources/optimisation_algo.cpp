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


std::array<parametres,NB_CLASSE_AGE> optimisation_algo_choice(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,Data data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init)
{   
    std::array<parametres,NB_CLASSE_AGE> param_opti;
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
std::array<parametres,NB_CLASSE_AGE> random_search(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init)
{
    
    double y[COMPARTIMENT*NB_CLASSE_AGE];
    std::array<parametres,NB_CLASSE_AGE> p;
    int output_model_return;
    std::array<parametres,NB_CLASSE_AGE> param_opti = cond_init;

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        set_condition_initiale(f[classe],param_opti[classe].x0,classe);
    }

    if (DISCRET == 1)
    {

        while (bb_discret(f,param_opti,data) !=0)
        {
            param_opti = set_parametres_random(random_ptr);
            
            for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
            {
                set_condition_initiale(f[classe],param_opti[classe].x0,classe);
            }
        }
    }else{
        
        write_result_conversion_ODE_to_vector(f, y, 0);

        integrate(f,param_opti,y);

    }
    

    
    double fct_obj = -fonction_obj(data,f,fct_obj_choice); ///////
    
    for (size_t i = 0; i < NB_ITE_BLACKBOX; i++)
    {   
                
        p = set_parametres_random(random_ptr);
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            set_condition_initiale(f[classe],p[classe].x0,classe);
        }
        
        std::cout << i << "   ";

        if (DISCRET == 1)
        {       
            if (bb_discret(f,p,data) == 0)
            {
                if(minimisation(fct_obj, data, f,fct_obj_choice))
                {
                    param_opti = p;
                }
            }
        }else{
  
            write_result_conversion_ODE_to_vector(f, y, 0);
            integrate(f,p,y);
            
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
std::array<parametres,NB_CLASSE_AGE> random_search_radius(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init)
{
    double radius = RADIUS_INIT;
    
    double y[COMPARTIMENT];

    std::array<parametres,NB_CLASSE_AGE> param_opti = cond_init;
    std::array<parametres,NB_CLASSE_AGE> p;


    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        set_condition_initiale(f[classe],param_opti[classe].x0,classe);
    }
    
    while (bb_discret(f,param_opti,data) !=0)
    {
        param_opti = set_parametres_random(random_ptr);
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            set_condition_initiale(f[classe],param_opti[classe].x0,classe);
        }
    }


    double fct_obj = -fonction_obj(data,f,fct_obj_choice); ///////
    
    for (size_t i = 0; i < NB_ITE_BLACKBOX; i++)
    {   

        if(i==NB_ITE_BLACKBOX-2)
        {
            i=0;
            

            if(radius < 0.001)
            {
                radius = radius/10;
            }else if(radius < 0.1){
                radius = radius/5;
            }else{
                radius = radius/1.5;
            }

        }
        if(radius < 0.00006)
        {
            break;
        }
         

        p = set_parametres_radius(random_ptr,param_opti,radius);
        
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            set_condition_initiale(f[classe],p[classe].x0,classe);
        }
        
        std::cout << i << "   " << radius << "   ";

        if (bb_discret(f,p,data) == 0)
        {
            if(minimisation(fct_obj, data, f,fct_obj_choice))
            {
                i=0;
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
std::array<parametres,NB_CLASSE_AGE> random_search_normal(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init)
{
    double sigma=SIGMA;
    
    double y[COMPARTIMENT*NB_CLASSE_AGE];

    std::array<parametres,NB_CLASSE_AGE> param_opti = cond_init;
    std::array<parametres,NB_CLASSE_AGE> p;


    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        set_condition_initiale(f[classe],param_opti[classe].x0,classe);
    }
    


    if (DISCRET == 1)
    {

        while (bb_discret(f,param_opti,data) !=0)
        {
            param_opti = set_parametres_random(random_ptr);
            
            for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
            {
                set_condition_initiale(f[classe],param_opti[classe].x0,classe);
            }
        }
    }else{

        
        
        write_result_conversion_ODE_to_vector(f, y, 0);

        integrate(f,param_opti,y);

    }


    double fct_obj = -fonction_obj(data,f,fct_obj_choice); ///////
    int save_intermediaire = 0;
    double accept_ite = 0;
    for (size_t i = 0; i < NB_ITE_BLACKBOX; i++)
    {   

        if(i==NB_ITE_BLACKBOX-2)
        {
            i=0;
            accept_ite = 0;

            sigma = sigma/2;

        }

        if(sigma < STOP_ALGO)
        {   

            break;
        }
        if (accept_ite > 200)
        {
            accept_ite = 0;
            sigma = sigma*1.3;
        }
        

        p = set_parametres_random_normal(random_ptr,sigma,param_opti);
        
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            set_condition_initiale(f[classe],p[classe].x0,classe);
        }
        
        std::cout << i << "   " << sigma << "   ";

        if (DISCRET == 1)
        {       
            if (bb_discret(f,p,data) == 0)
            {
                if(minimisation(fct_obj, data, f,fct_obj_choice))
                {
                    i=0;
                    accept_ite++;
                    param_opti = p;
                }
            }else{i--;}
        }else{
  
            write_result_conversion_ODE_to_vector(f, y, 0);
            integrate(f,p,y);
            
            if(minimisation(fct_obj, data, f,fct_obj_choice))
            {
                i=0;
                accept_ite++;
                param_opti = p;
            }

        }



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