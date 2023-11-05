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
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_obj.hpp"
#include "../headers/fonction_discret.hpp"
#include "../headers/optimisation_algo.hpp"


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> set_parametres_random_normal(gsl_rng* r,double sigma,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_opt)
{
    switch (MCMC_PARAM_TYPE_SELECTION)
    {
    case 0:
        return set_parametres_random_normal_all(r,sigma, p_opt);
        break;
    case 1:
        return set_parametres_random_normal_gibbs(r,sigma,p_opt);

    
    default:
        break;
    }
}


/**
 * @brief retourne des parametres à partir d'une loi normale centre en p_opt et d'écart-type sigma
 *     Social_contact_matrix.cpprametres contenant les parametres optimaux par classe d'age, trouvé par l'algo
 */
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> set_parametres_random_normal_all(gsl_rng* r,double sigma,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_opt)
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    int ite=0;

    do
    {   

        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            for (size_t param_id = 0; param_id < NB_PARAM_TOT; param_id++)
            {
                ite = NB_PARAM_TOT*classe + param_id;
                if (param_id == PARAM_ID_X0_infect)
                {
                    p[NB_PARAM_TOT*classe + param_id]= p_opt[NB_PARAM_TOT*classe + param_id] + gsl_ran_gaussian(r, sigma)*(5000/POP_TOT);
                }
                else
                {
                    p[NB_PARAM_TOT*classe + param_id]= p_opt[NB_PARAM_TOT*classe + param_id] + gsl_ran_gaussian(r, sigma);
                }
            }
            
        }
        
    } while (! validation_parametres(p));

    return p;
}


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> set_parametres_random_normal_gibbs(gsl_rng* r,double sigma,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p_opt)
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    int ite=0;
    int param_id;
    int classe;
    double y;
    
    do
    {   
        p=p_opt;
        param_id = gsl_rng_uniform_int(r,NB_PARAM_TOT);
        classe = gsl_rng_uniform_int(r,NB_CLASSE_AGE);
        
        if (param_id == PARAM_ID_X0_infect)
        {
            p[NB_PARAM_TOT*classe + param_id]= p_opt[NB_PARAM_TOT*classe + param_id] + gsl_ran_gaussian(r, sigma)*(5000/POP_TOT);
        }
        else
        {
            p[NB_PARAM_TOT*classe + param_id]= p_opt[NB_PARAM_TOT*classe + param_id] + gsl_ran_gaussian(r, sigma);
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
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> set_parametres_random(gsl_rng* r)
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    double y;
    do
    {   
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {        
            for (size_t param_id = 0; param_id < NB_PARAM_TOT; param_id++)
            {
                if (param_id == PARAM_ID_X0_infect)
                {
                    p[NB_PARAM_TOT*classe + param_id]= gsl_rng_uniform(r)*(4478.0/POP_TOT);
                }
                else 
                {
                    y = gsl_rng_uniform(r);
                    double a = NB_PARAM_TOT*classe + param_id;
                    p[NB_PARAM_TOT*classe + param_id] = y;
                }
            }
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
/*
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
                p[classe].x0[I_COMP] = p_opt[classe].x0[I_COMP] + ((gsl_rng_uniform(r)*(4478/POP_TOT)*2)-(4478/POP_TOT))*radius;
                p[classe].x0[S_COMP] = PROP_PAR_CLASSE[classe]-p[classe].x0[I_COMP];
                p[classe].x0[R_COMP] = 0;
                p[classe].x0[Q_COMP] = 0;
                p[classe].x0[D_COMP] = 0;
            }
        }
    } while (! validation_parametres(p));

    

    return p;

}
*/
void conversion(const std::array<parametres,NB_CLASSE_AGE>& p_struct,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p_tab)
{
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        p_tab[NB_PARAM_TOT*classe + PARAM_ID_DELTA] = p_struct[classe].delta;
        p_tab[NB_PARAM_TOT*classe + PARAM_ID_GAMMA] = p_struct[classe].gamma;
        p_tab[NB_PARAM_TOT*classe + PARAM_ID_EPS] = p_struct[classe].eps;
        p_tab[NB_PARAM_TOT*classe + PARAM_ID_R] = p_struct[classe].r;

        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 0] = p_struct[classe].beta[0];
        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 1] = p_struct[classe].beta[1];
        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 2] = p_struct[classe].beta[2];
        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 3] = p_struct[classe].beta[3];
        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 4] = p_struct[classe].beta[4];
        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 5] = p_struct[classe].beta[5];
        p_tab[NB_PARAM_TOT*classe + NB_PARAM + 6] = p_struct[classe].beta[6];
    }
    
}




/**
 * @brief valide ou non les parametres contenu dans le tableau de parametres p
 * 
 * @param p tableau de paremetres de taille NB_CLASSE_AGE devant être validé
 * @return true si les parametres sont valides
 * @return false sinon
 */
bool validation_parametres(const std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p){
    
    bool ok=true;
    double somme1 = 0;
    double somme = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
    
        for (int i = 0; i < NB_CONFINEMENT+1; i++)
        {
            if(p[NB_PARAM_TOT*classe + PARAM_ID_BETA0 + i] >1 || p[NB_PARAM_TOT*classe + PARAM_ID_BETA0 + i] <0){
                ok=false;  
                
            }
        }

        if(p[NB_PARAM_TOT*classe + PARAM_ID_DELTA]>1 || p[NB_PARAM_TOT*classe + PARAM_ID_DELTA]<0){
            ok=false;  
             
        }
        if(p[NB_PARAM_TOT*classe + PARAM_ID_GAMMA]>1 || p[NB_PARAM_TOT*classe + PARAM_ID_GAMMA]<0){
            ok=false; 
               
        }
        if(p[NB_PARAM_TOT*classe + PARAM_ID_EPS]>1 || p[NB_PARAM_TOT*classe + PARAM_ID_EPS]<0){
            ok=false;   
             
        }
        if(p[NB_PARAM_TOT*classe + PARAM_ID_R]>1 || p[NB_PARAM_TOT*classe + PARAM_ID_R]<0){
            ok=false;    
        }
        if(p[NB_PARAM_TOT*classe + PARAM_ID_DELTA] + p[NB_PARAM_TOT*classe + PARAM_ID_GAMMA]>1 || p[NB_PARAM_TOT*classe + PARAM_ID_EPS] + p[NB_PARAM_TOT*classe + PARAM_ID_R] >1){
            ok=false;
        }

        if(p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect] < 0 || p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect] > 4478/POP_TOT){
            ok=false;
        } 

        somme1 = somme1 + p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect];

    }

    if(somme1 < 1/POP_TOT || somme1 > 4478/POP_TOT){
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

