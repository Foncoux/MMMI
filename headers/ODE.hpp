#ifndef ODE_HPP
#define ODE_HPP

class ODE
{
    private : 
        
        
        
    public :
        
        int (*m_function_discret)(std::array<std::array<double, NB_DAY> , COMPARTIMENT_TOT> &,parametres,int,double);
        int (*m_function_discret_new)(std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT> &y,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,int n,double lambda, int classe, int i);
        int (*m_function)(double, const double [], double [],void*);
        int (*m_jacobian)(double, const double [], double *, double [], void *);
        std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT> m_result_integration;
        std::array<std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT>,NB_CLASSE_AGE> m_result_simulation;

        ODE();
        
};

void set_condition_initiale(ODE &f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> &p);

#endif
