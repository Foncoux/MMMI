#include "../headers/blackbox.hpp"

parametres set_parametres(gsl_rng* r,parametres p_opt){
    
    parametres p;
    

    do
    {
        /*
        p.beta = gsl_rng_uniform(r)*5;
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
        */


        p.beta = p_opt.beta + ((gsl_rng_uniform(r)*5*2)-5)*0.1;
        p.delta = p_opt.delta + (gsl_rng_uniform(r)*2-1)*0.1; // Générer un nombre aléatoire compris entre 0 et 1
        p.eps = p_opt.eps + (gsl_rng_uniform(r)*2-1)*0.1;
        p.gamma = p_opt.gamma + (gsl_rng_uniform(r)*2-1)*0.1;
        p.r = p_opt.r + (gsl_rng_uniform(r)*2-1)*0.1;

        
    } while (! validation_parametres(p));

    

    return p;

}

bool validation_parametres(const parametres p){
    
    bool ok=true;
    
    if(p.beta >5 || p.beta<0){
        ok=false;  
    }
    //if(x0[1]>0.00001 || x0[1]<0.0000001){
    //   ok=false;    
    //} 
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

