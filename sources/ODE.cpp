#include "../headers/ODE.hpp"



ODE::ODE(int fct_choice=3)
{   
    switch (fct_choice)
    {
    case 1:

        m_function = oscillateur_harm; 
        m_jacobian = jacobian_osc; 

        break;
    case 2:

        m_function = SIRQD; 
        m_jacobian = jacobian_SIRQD; 

        break;
    case 3:
        m_function_discret = SIRQD_discret;
    
    default:
        break;
    }

}

void ODE::set_condition_initiale(double y[])
{
    m_result_integration[0][0] = y[0];
    m_result_integration[1][0] = y[1];
    m_result_integration[2][0] = y[2];
    m_result_integration[3][0] = y[3];
    m_result_integration[4][0] = y[4];
}

/* write data envisageable dans la classe*/