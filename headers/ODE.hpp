#ifndef ODE_HPP
#define ODE_HPP

#include <array>
#include <iostream>
#include <fstream>
#include "../headers/functions.hpp"
#include "../config/config.hpp"
#include "../headers/fonction_discret.hpp"

class ODE
{
    private : 
        
        
        
    public :
        
        void (*m_function_discret)(std::array<std::array<double, T_FINAL> , COMPARTIMENT> &,parametres,int);

        std::array<std::array<double, T_FINAL>, COMPARTIMENT> m_result_integration;

        ODE(int fct_choice);
        
};

void set_condition_initiale(ODE f[],std::array<std::array<double, COMPARTIMENT> , NB_CLASSE_AGE> &cond_init);


#endif
