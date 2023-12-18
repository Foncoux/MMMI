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

#include "nomad/Nomad/nomad.hpp"




ODE::ODE()
{   
    switch (MODEL_BB)
    {
    case 4:
        m_function_discret_new = SIRQD_discret_new;
    
    case 5:
        m_function_discret_nomad = SIRQD_discret_new;
    default:
        break;
    }





}

void set_condition_initiale(ODE &f,const NOMAD::EvalPoint &p)
{
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        f.m_result_simulation[classe][I_COMP][0] = p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect].todouble();
        f.m_result_simulation[classe][S_COMP][0] = PROP_PAR_CLASSE[classe] - p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect].todouble();
        f.m_result_simulation[classe][R_COMP][0] = 0;
        f.m_result_simulation[classe][Q_COMP][0] = 0;
        f.m_result_simulation[classe][D_COMP][0] = 0;
        f.m_result_simulation[classe][Q_ENTRY_COMP][0] = 0;
        f.m_result_simulation[classe][D_ENTRY_COMP][0] = 0;
    }
       
}

void set_condition_initiale(ODE &f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> &p)
{
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        f.m_result_simulation[classe][I_COMP][0] = p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect];
        f.m_result_simulation[classe][S_COMP][0] = PROP_PAR_CLASSE[classe] - p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect];
        f.m_result_simulation[classe][R_COMP][0] = 0;
        f.m_result_simulation[classe][Q_COMP][0] = 0;
        f.m_result_simulation[classe][D_COMP][0] = 0;
        f.m_result_simulation[classe][Q_ENTRY_COMP][0] = 0;
        f.m_result_simulation[classe][D_ENTRY_COMP][0] = 0;
    }
       
}

