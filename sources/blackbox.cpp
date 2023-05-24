#include "../headers/blackbox.hpp"


#include <iostream>
#include <array>
#include "../headers/integration.hpp"
#include "../headers/blackbox.hpp"

#include "../headers/functions.hpp"

#include "../config/config.hpp"
#include "../headers/ODE.hpp"

#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_obj.hpp"
#include "../headers/fonction_discret.hpp"

#include <algorithm>

void bb(ODE &f, parametres p, double y[])
{
    integrate(f,p,y);
}

void bb_discret(ODE f[],parametres p)
{
    std::cout << "test bb_discret   "  << std::endl; 
    p.i=0;
    
    
    for (int n = 0; n < T_FINAL-1; n++)
    {   
        
        
        if(std::find(TAB_DATE_CONFINEMENT.begin(), TAB_DATE_CONFINEMENT.end(), n) != TAB_DATE_CONFINEMENT.end()){
            p.i++;
        }

        for (size_t i = 0; i < NB_CLASSE_AGE; i++)
        {
            f[i].m_function_discret(f[i].m_result_integration,p,n);////    
        }
        std::cout << "test bb_discret after    "  << std::endl ;
    }
    
}

/*
parametres random_search(gsl_rng* random_ptr,ODE &f,std::array<double,DEATH_NB_DAY> death,std::array<double,HOSP_NB_DAY> hosp)
{
    double y[COMPARTIMENT];

    parametres param_opti = set_parametres_random(random_ptr);      
    std::copy(std::begin(param_opti.x0), std::end(param_opti.x0), std::begin(y));

    f.set_condition_initiale(y);
    bb(f,param_opti,y);

    double fct_obj = fonction_obj(death, hosp, f);

    parametres p = set_parametres_random(random_ptr);
    
    

    for (size_t i = 0; i < 10000; i++)
    {   
                
        parametres p = set_parametres_random(random_ptr);
        std::copy(std::begin(p.x0), std::end(p.x0), std::begin(y));
        f.set_condition_initiale(y);

        bb(f,p,y);

        std::cout << i << "   " << "\n";

        if(minimisation(fct_obj, death, hosp, f.m_result_integration))
        {
            param_opti = p;
        }
    }

    std::cout << fct_obj << std::endl;

    return param_opti;
  
}
*/

parametres random_search_radius(gsl_rng* random_ptr,ODE f[],std::array<double,DEATH_NB_DAY> death,std::array<double,HOSP_NB_DAY> hosp, std::array<std::array<std::array<double, T_FINAL>, COMPARTIMENT>, NB_CLASSE_AGE> &model_result)
{
    double radius = 0.2;
    double y[COMPARTIMENT];

    parametres param_opti = set_parametres_random(random_ptr);
    
    

    if(DISCRET == 0)
    {      
    /*
        std::copy(std::begin(param_opti.x0), std::end(param_opti.x0), std::begin(y));
        f.set_condition_initiale(y); 
        bb(f,param_opti,y);
    */
    }else if(DISCRET == 1)
    {
        for (size_t i = 0; i < NB_CLASSE_AGE; i++)
        {
            f[i].set_condition_initiale(param_opti.x0);
        }
        
        std::cout << "test random radius   "  << std::endl ; 
        bb_discret(f,param_opti);
        
    }

    
    double fct_obj = fonction_obj(death, hosp, f); ///////
    
    for (size_t i = 0; i < 20000; i++)
    {   
                
        parametres p = set_parametres_radius(random_ptr,param_opti,radius);
        if(DISCRET == 0)
        {
            /*
            std::copy(std::begin(p.x0), std::end(p.x0), std::begin(y));
            f.set_condition_initiale(y);
            bb(f,p,y);
            */
        }else if(DISCRET == 1)
        {
            for (size_t i = 0; i < NB_CLASSE_AGE; i++)
            {
                f[i].set_condition_initiale(p.x0);
            }
            
            bb_discret(f,p);
        }
        

        std::cout << i << "   ";

        if(minimisation(fct_obj, death, hosp, f))
        {
            param_opti = p;
        }
    }

    std::cout << fct_obj << std::endl;

    return param_opti;
  

}

parametres set_parametres_random(gsl_rng* r)
{
    parametres p;
    
    do
    {
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
        {
            p.beta[i] = gsl_rng_uniform(r);
        }
        
        
        if(gsl_rng_uniform(r) < 0.5){
            p.delta = gsl_rng_uniform(r); // Générer un nombre aléatoire compris entre 0 et 1
            p.gamma = gsl_rng_uniform(r)*(1-p.delta);
        }else{
            p.gamma = gsl_rng_uniform(r);
            p.delta = gsl_rng_uniform(r)*(1-p.gamma); // Générer un nombre aléatoire compris entre 0 et 1
        }
        
        if(gsl_rng_uniform(r) < 0.5){
            p.eps = gsl_rng_uniform(r);
            p.r = gsl_rng_uniform(r)*(1-p.eps);
        }else{
            p.r = gsl_rng_uniform(r);
            p.eps = gsl_rng_uniform(r)*(1-p.r);
            
        }

        p.x0[I_COMP] = gsl_rng_uniform(r)*(100/POP_TOT);
        p.x0[S_COMP] = 1-p.x0[I_COMP];
        
    } while (! validation_parametres(p));
    
    return p;
}

parametres set_parametres_radius(gsl_rng* r,parametres p_opt,double radius){
    
    parametres p;
    

    do
    {
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
        {
            p.beta[i] = p_opt.beta[i] + ((gsl_rng_uniform(r)*2)-1)*radius;
        }

        p.delta = p_opt.delta + (gsl_rng_uniform(r)*2-1)*radius; // Générer un nombre aléatoire compris entre 0 et 1
        p.eps = p_opt.eps + (gsl_rng_uniform(r)*2-1)*radius;
        p.gamma = p_opt.gamma + (gsl_rng_uniform(r)*2-1)*radius;
        p.r = p_opt.r + (gsl_rng_uniform(r)*2-1)*radius;

        p.x0[I_COMP] = (gsl_rng_uniform(r)*(100/POP_TOT)*2-(100/POP_TOT))*radius;
        p.x0[S_COMP] = 1-p.x0[I_COMP];
        
    } while (! validation_parametres(p));

    

    return p;

}

bool validation_parametres(const parametres p){
    
    bool ok=true;
    
    for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
    {
        if(p.beta[i] >1 || p.beta[i]<0){
        ok=false;  
    }
    }
    
    
    if(p.x0[1]< 1/POP_TOT || p.x0[1] > 100/POP_TOT){
       ok=false;    
    } 
    if(p.delta>1 || p.delta<0){
        ok=false;   
    }
    if(p.gamma>1 || p.gamma<0){
        ok=false;    
    }
    if(p.eps>1 || p.eps<0){
        ok=false;    
    }
    if(p.r>1 || p.r<0){
        ok=false;    
    }
    if(p.delta + p.gamma >1 || p.eps + p.r >1){
        ok=false;
    }

    return ok;
}

