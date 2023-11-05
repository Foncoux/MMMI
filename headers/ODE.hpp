#ifndef ODE_HPP
#define ODE_HPP

class ODE
{
    private : 
        
        
        
    public :
        
        int (*m_function_discret)(std::array<std::array<double, T_FINAL> , COMPARTIMENT_TOT> &,parametres,int,double);
        int (*m_function_discret_new)(std::array<std::array<double, T_FINAL>, COMPARTIMENT_TOT> &y,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,int n,double lambda, int classe, int i);
        int (*m_function)(double, const double [], double [],void*);
        int (*m_jacobian)(double, const double [], double *, double [], void *);
        std::array<std::array<double, T_FINAL>, COMPARTIMENT_TOT> m_result_integration;

        ODE();
        
};

void set_condition_initiale(ODE& f,double cond_init_infect,int classe);


#endif
