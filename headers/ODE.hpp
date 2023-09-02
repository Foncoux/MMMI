#ifndef ODE_HPP
#define ODE_HPP

class ODE
{
    private : 
        
        
        
    public :
        
        int (*m_function_discret)(std::array<std::array<double, T_FINAL> , COMPARTIMENT> &,parametres,int,double);
        int (*m_function)(double, const double [], double [],void*);
        int (*m_jacobian)(double, const double [], double *, double [], void *);
        std::array<std::array<double, T_FINAL>, COMPARTIMENT> m_result_integration;

        ODE();
        
};

void set_condition_initiale(ODE& f,std::array<std::array<double, COMPARTIMENT> , NB_CLASSE_AGE> &cond_init,int classe);


#endif
