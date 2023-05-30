#include "../headers/blackbox.hpp"


#include <iostream>
#include <array>

#include "../headers/blackbox.hpp"

#include "../headers/functions.hpp"

#include "../config/config.hpp"
#include "../headers/ODE.hpp"

#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_obj.hpp"
#include "../headers/fonction_discret.hpp"

#include <algorithm>

void bb_discret(ODE f[],parametres p)
{
   
    p.i=0;
    
    
    for (int n = 0; n < NB_DAY-1; n++)
    {   
        
        
        if(std::find(TAB_DATE_CONFINEMENT.begin(), TAB_DATE_CONFINEMENT.end(), n) != TAB_DATE_CONFINEMENT.end()){
            p.i++;
        }

        for (size_t i = 0; i < NB_CLASSE_AGE; i++)
        {
            f[i].m_function_discret(f[i].m_result_integration,p,n);////    
        }

    }
    
}


parametres random_search(gsl_rng* random_ptr,ODE f[],const Data &data)
{
    
    double y[COMPARTIMENT];

    parametres param_opti = set_parametres_random(random_ptr);

    set_condition_initiale(f,param_opti.x0);
    
    bb_discret(f,param_opti);

    
    double fct_obj = fonction_obj(data,f); ///////
    
    for (size_t i = 0; i < 300000; i++)
    {   
                
        parametres p = set_parametres_random(random_ptr);
        
        set_condition_initiale(f,p.x0);
        
        bb_discret(f,p);
        
        

        std::cout << i << "   ";

        if(minimisation(fct_obj, data, f))
        {
            param_opti = p;
        }
    }

    std::cout << fct_obj << std::endl;

    return param_opti;
  

}



parametres random_search_radius(gsl_rng* random_ptr,ODE f[],const Data &data)
{
    double radius = 0.2;
    double y[COMPARTIMENT];

    parametres param_opti = set_parametres_random(random_ptr);
    
    set_condition_initiale(f,param_opti.x0);
    
    bb_discret(f,param_opti); 

    double fct_obj = fonction_obj(data,f); ///////
    
    for (size_t i = 0; i < 100000; i++)
    {   
                
        parametres p = set_parametres_radius(random_ptr,param_opti,radius);
        
        
        set_condition_initiale(f,p.x0);
        bb_discret(f,p);
        
        

        std::cout << i << "   ";

        if(minimisation(fct_obj, data, f))
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

        //p.x0[I_COMP] = gsl_rng_uniform(r)*(5000/POP_TOT);

        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            p.x0[classe][I_COMP] = gsl_rng_uniform(r)*(4478/POP_TOT);
            p.x0[classe][S_COMP] = 1-p.x0[classe][I_COMP];
            p.x0[classe][R_COMP] = 0;
            p.x0[classe][Q_COMP] = 0;
            p.x0[classe][D_COMP] = 0;
        }
        
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

        //p.x0[I_COMP] = (gsl_rng_uniform(r)*(5000/POP_TOT)*2-(5000/POP_TOT))*radius;
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            p.x0[classe][I_COMP] = gsl_rng_uniform(r)*(4478/POP_TOT);
            p.x0[classe][S_COMP] = 1-p.x0[classe][I_COMP];
            p.x0[classe][R_COMP] = 0;
            p.x0[classe][Q_COMP] = 0;
            p.x0[classe][D_COMP] = 0;
        }
        
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
    
    /*
    if(p.x0[1]< 1/POP_TOT || p.x0[1] > 5000/POP_TOT){
       ok=false;    
    } 
    */
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

