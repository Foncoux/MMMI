#include "../headers/ODE.hpp"




ODE::ODE(int fct_choice,double y[])
{   
    switch (fct_choice)
    {
    case 1:
        m_result_integration[0][0] = y[0];
        m_result_integration[1][0] = y[1];

        m_function = oscillateur_harm; 
        m_jacobian = jacobian_osc; 

        break;
    case 2:
        m_result_integration[0][0] = y[0];
        m_result_integration[1][0] = y[1];
        m_result_integration[2][0] = y[2];
        m_result_integration[3][0] = y[3];
        m_result_integration[4][0] = y[4];

        m_function = SIRQD; 
        m_jacobian = jacobian_SIRQD; 

        break;
    
    default:
        break;
    }

}

/*
void ODE::evaluate(std::vector<double>& x)
{
    m_function(x);
}
*/
/*
const std::vector<std::vector<double>>& ODE::get_result_integration(){
    return m_result_integration;
}
*/
/*
void ODE::resize_result_integration(int taille, int compartiment)
{
    m_result_integration.resize(compartiment);
    for (int i = 0; i < compartiment; ++i)
    {
        m_result_integration[i].resize(taille);
    }
}
*/

/*
void ODE::writeData(int taille,int compartiment)
{
    std::ofstream file("../data/integration.txt");
    if(file)
    {
    
        
        for (int j = 0; j < compartiment; j++)
        {
            for (int i = 0; i < taille-1; i++)
            {
                file << m_result_integration[j][i] << " " ;
            }
            file << std::endl;
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
    return;
}

*/