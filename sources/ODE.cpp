/**
 * @file ODE.cpp
 * @author Esteban Foncoux
 * @brief permet de stocker la modèle épidémiologique utilisé
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <gsl/gsl_rng.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"

#include "../headers/fonction_discret.hpp"
#include "../headers/fonction_continuous.hpp"




ODE::ODE()
{   
    switch (MODEL)
    {

    case 1:
        m_function_discret = SIRQD_discret;
        for(auto& subArray : m_result_integration) {
            subArray.fill(0.0);
        }

        break;
            
    case 2:
        m_function = oscillateur_harm; 
        m_jacobian = jacobian_osc; 
        break;
    
    case 3:
        m_function = model_SIRQD; 
        m_jacobian = jacobian_SIRQD;
        break; 

    case 4:
        m_function_discret_new = SIRQD_discret_new;
        for(auto& subArray : m_result_integration) {
            subArray.fill(0.0);
        }
    default:
        break;
    }





}


void set_condition_initiale(ODE &f,double cond_init_infect,int classe)
{
   
    f.m_result_integration[I_COMP][0] = cond_init_infect;
    f.m_result_integration[S_COMP][0] = PROP_PAR_CLASSE[classe] - cond_init_infect;
    f.m_result_integration[R_COMP][0] = 0;
    f.m_result_integration[Q_COMP][0] = 0;
    f.m_result_integration[D_COMP][0] = 0;
    
    
}

