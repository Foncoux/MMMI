#include "../headers/ODE.hpp"




ODE::ODE(int fct_choice)
{   
    switch (fct_choice)
    {
    case 1:
        m_compartiment = 2;
        m_function = oscillateur_harm; 

        break;
    
    default:
        break;
    }

}

void ODE::evaluate(std::vector<double>& x)
{
    m_function(x);
}


const std::vector<std::vector<double>>& ODE::get_result_integration(){
    return m_result_integration;
}


void ODE::resize_result_integration(int taille, int compartiment)
{
    m_result_integration.resize(compartiment);
    for (int i = 0; i < compartiment; ++i)
    {
        m_result_integration[i].resize(taille);
    }
}

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

