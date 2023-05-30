#include "../headers/ODE.hpp"



ODE::ODE(int fct_choice=3)
{   
    switch (fct_choice)
    {

    case 3:
        m_function_discret = SIRQD_discret;

        break;
            
    default:
        break;
    }

}


void set_condition_initiale(ODE f[],std::array<std::array<double, COMPARTIMENT> , NB_CLASSE_AGE> &cond_init)
{
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        f[classe].m_result_integration[S_COMP][0] = cond_init[classe][S_COMP];
        f[classe].m_result_integration[I_COMP][0] = cond_init[classe][I_COMP];
        f[classe].m_result_integration[R_COMP][0] = cond_init[classe][R_COMP];
        f[classe].m_result_integration[Q_COMP][0] = cond_init[classe][Q_COMP];
        f[classe].m_result_integration[D_COMP][0] = cond_init[classe][D_COMP];
    }
    
}

