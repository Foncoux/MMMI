#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
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
#include "../headers/fonction_obj.hpp"
#include "../headers/fonction_discret.hpp"
#include "../headers/optimisation_algo.hpp"






/**
 * @brief retourne des parametres à partir d'une loi normale centre en p_opt et d'écart-type sigma
 *     Social_contact_matrix.cpprametres contenant les parametres optimaux par classe d'age, trouvé par l'algo
 */
std::array<parametres,NB_CLASSE_AGE> set_parametres_random_normal(gsl_rng* r,double sigma,std::array<parametres,NB_CLASSE_AGE> p_opt)
{
    std::array<parametres,NB_CLASSE_AGE> p;
    int ite=0;

    do
    {   
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
            {
                p[classe].beta[i] = p_opt[classe].beta[i] + gsl_ran_gaussian(r, sigma);
            }

            p[classe].delta = p_opt[classe].delta + gsl_ran_gaussian(r, sigma); // Générer un nombre aléatoire compris entre 0 et 1
            p[classe].eps = p_opt[classe].eps + gsl_ran_gaussian(r, sigma);
            p[classe].gamma = p_opt[classe].gamma + gsl_ran_gaussian(r, sigma);
            p[classe].r = p_opt[classe].r + gsl_ran_gaussian(r, sigma);

            p[classe].sigma = 1.0/5.5;
            //p.x0[I_COMP] = (gsl_rng_uniform(r)*(5000/POP_TOT)*2-(5000/POP_TOT))*radius;


            p[classe].x0[classe][I_COMP] = p_opt[classe].x0[classe][I_COMP] + gsl_ran_gaussian(r, sigma/10000);
//            p[classe].x0[classe][E_COMP] = p[classe].x0[classe][I_COMP];
//            p[classe].x0[classe][S_COMP] = PROP_PAR_CLASSE[classe]-p[classe].x0[classe][I_COMP]-p[classe].x0[classe][E_COMP];
            p[classe].x0[classe][S_COMP] = PROP_PAR_CLASSE[classe]-p[classe].x0[classe][I_COMP];
            p[classe].x0[classe][R_COMP] = 0;
            p[classe].x0[classe][Q_COMP] = 0;
            p[classe].x0[classe][D_COMP] = 0;
            
            
        }
        
    } while (! validation_parametres(p));

    return p;
}



/**
 * @brief défini aléatoirement des parametres
 * 
 * @param r pointeurs pour l'aléatoire
 * @return std::array<parametres,NB_CLASSE_AGE> tableau de parametres contenant les parametres optimaux par classe d'age, trouvé par l'algo
 */
std::array<parametres,NB_CLASSE_AGE> set_parametres_random(gsl_rng* r)
{
    std::array<parametres,NB_CLASSE_AGE> p;
    
    do
    {
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
            {
                p[classe].beta[i] = gsl_rng_uniform(r);
            }
            
            
            if(gsl_rng_uniform(r) < 0.5){
                p[classe].delta = gsl_rng_uniform(r); // Générer un nombre aléatoire compris entre 0 et 1
                p[classe].gamma = gsl_rng_uniform(r)*(1-p[classe].delta);
            }else{
                p[classe].gamma = gsl_rng_uniform(r);
                p[classe].delta = gsl_rng_uniform(r)*(1-p[classe].gamma); // Générer un nombre aléatoire compris entre 0 et 1
            }
            
            if(gsl_rng_uniform(r) < 0.5){
                p[classe].eps = gsl_rng_uniform(r);
                p[classe].r = gsl_rng_uniform(r)*(1-p[classe].eps);
            }else{
                p[classe].r = gsl_rng_uniform(r);
                p[classe].eps = gsl_rng_uniform(r)*(1-p[classe].r);
                
            }
            p[classe].sigma = 1.0/5.5;

            //p.x0[I_COMP] = gsl_rng_uniform(r)*(5000/POP_TOT);

            
            
                
            p[classe].x0[classe][I_COMP] = gsl_rng_uniform(r)*(4478/POP_TOT);
//            p[classe].x0[classe][E_COMP] = p[classe].x0[classe][I_COMP];
//            p[classe].x0[classe][S_COMP] = PROP_PAR_CLASSE[classe]-p[classe].x0[classe][I_COMP]-p[classe].x0[classe][E_COMP];
            p[classe].x0[classe][S_COMP] = PROP_PAR_CLASSE[classe]-p[classe].x0[classe][I_COMP];
            p[classe].x0[classe][R_COMP] = 0;
            p[classe].x0[classe][Q_COMP] = 0;
            p[classe].x0[classe][D_COMP] = 0;
                
            
            
        } 
    }while (! validation_parametres(p));


    return p;
}


/**
 * @brief défini des parametres dans une boule de rayon radius autour des parametres p_opt
 * 
 * @param r pointeurs gsl pour l'aléatoire
 * @param p_opt tableau de parametres de taille NB_CLASSE_AGE étant le centre de la boule
 * @param radius rayon de la boule
 * @return std::array<parametres,NB_CLASSE_AGE> tableau de parametres contenant les parametres optimaux par classe d'age, trouvé par l'algo
 */
std::array<parametres,NB_CLASSE_AGE> set_parametres_radius(gsl_rng* r,std::array<parametres,NB_CLASSE_AGE> p_opt,double radius){
    
    std::array<parametres,NB_CLASSE_AGE> p;
    

    do
    {
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
            {
                p[classe].beta[i] = p_opt[classe].beta[i] + ((gsl_rng_uniform(r)*2)-1)*(radius);
            }

            p[classe].delta = p_opt[classe].delta + (gsl_rng_uniform(r)*2-1)*radius; // Générer un nombre aléatoire compris entre 0 et 1
            p[classe].eps = p_opt[classe].eps + (gsl_rng_uniform(r)*2-1)*radius;
            p[classe].gamma = p_opt[classe].gamma + (gsl_rng_uniform(r)*2-1)*radius;
            p[classe].r = p_opt[classe].r + (gsl_rng_uniform(r)*2-1)*radius;

            //p.x0[I_COMP] = (gsl_rng_uniform(r)*(5000/POP_TOT)*2-(5000/POP_TOT))*radius;
            for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
            {
                p[classe].x0[classe][I_COMP] = p_opt[classe].x0[classe][I_COMP] + ((gsl_rng_uniform(r)*(4478/POP_TOT)*2)-(4478/POP_TOT))*radius;
                p[classe].x0[classe][S_COMP] = PROP_PAR_CLASSE[classe]-p[classe].x0[classe][I_COMP];
                p[classe].x0[classe][R_COMP] = 0;
                p[classe].x0[classe][Q_COMP] = 0;
                p[classe].x0[classe][D_COMP] = 0;
            }
        }
    } while (! validation_parametres(p));

    

    return p;

}

/**
 * @brief valide ou non les parametres contenu dans le tableau de parametres p
 * 
 * @param p tableau de paremetres de taille NB_CLASSE_AGE devant être validé
 * @return true si les parametres sont valides
 * @return false sinon
 */
bool validation_parametres(const std::array<parametres,NB_CLASSE_AGE> p){
    
    bool ok=true;
    double somme1 = 0;
    double somme = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
    
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
        {
            if(p[classe].beta[i] >1 || p[classe].beta[i]<0){
                ok=false;  
                
            }
        }

        if(p[classe].delta>1 || p[classe].delta<0){
            ok=false;  
             
        }
        if(p[classe].gamma>1 || p[classe].gamma<0){
            ok=false; 
               
        }
        if(p[classe].eps>1 || p[classe].eps<0){
            ok=false;   
             
        }
        if(p[classe].r>1 || p[classe].r<0){
            ok=false;    
        }
        if(p[classe].delta + p[classe].gamma >1 || p[classe].eps + p[classe].r >1){
            ok=false;
        }

        if(p[classe].x0[classe][I_COMP] < 0 || p[classe].x0[classe][I_COMP] > 4478/POP_TOT){
            ok=false;
        } 

        for (size_t compart = 0; compart < COMPARTIMENT; compart++)
        {         
            somme = somme + p[classe].x0[classe][compart];
        }

        somme1 = somme1 + p[classe].x0[classe][I_COMP];


    }

    if(somme1 < 1/POP_TOT || somme1 > 4478/POP_TOT){
        ok=false;
    } 

    double epsilon = GSL_DBL_EPSILON;
    if (gsl_fcmp(somme, 1, epsilon) != 0 )
    {
        ok=false;
    }

/*
    if (p[0].r > p[1].r)
    {
        ok=false;
    }
    if (p[0].delta > p[1].delta)
    {
        ok=false;
    }
    if (p[0].gamma < p[1].gamma)
    {
        ok=false;
    }
    if (p[0].eps < p[1].eps)
    {
        ok=false;
    }

    */
    /*
    if (p[0].beta[3] > p[0].beta[0] || p[0].beta[3] > p[0].beta[1] || p[0].beta[3] > p[0].beta[2])
    {
        ok=false;
    }
    if (p[0].beta[4] > p[0].beta[0] || p[0].beta[4] > p[0].beta[1] || p[0].beta[4] > p[0].beta[2])
    {
        ok=false;
    }
    if (p[1].beta[4] > p[1].beta[0] || p[1].beta[4] > p[1].beta[1] || p[1].beta[4] > p[1].beta[2])
    {
        ok=false;
    }
    */
    return ok;
}

