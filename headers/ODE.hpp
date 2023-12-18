#ifndef ODE_HPP
#define ODE_HPP
#include "Nomad_file.hpp"

class ODE
{
    private : 
        
        
        
    public :
        
        int (*m_function_discret_nomad)(std::array<std::array<double, NB_DAY> , COMPARTIMENT_TOT> &,const NOMAD::EvalPoint &,int,double,int,int);
        int (*m_function_discret_new)(std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT> &y,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,int n,double lambda, int classe, int i);


        std::array<std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT>,NB_CLASSE_AGE> m_result_simulation;

        ODE();
        
};

void set_condition_initiale(ODE &f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> &p);
void set_condition_initiale(ODE &f,const NOMAD::EvalPoint &p);

#endif
