
#include "../headers/integrator.hpp"


void RK4(ODE &f, double a, double b, double h,int taille, std::vector<double> &x0,int compartiment)
{   

    f.resize_result_integration(taille,compartiment);


    std::vector<double> K1(compartiment);
    std::vector<double> K2(compartiment);
    std::vector<double> K3(compartiment);
    std::vector<double> K4(compartiment);

    double t=0;

    for(int i = 0; i < compartiment; i++)
    {
        f.m_result_integration[i][0] = x0[i];
    }

    for (int i = 0; i < taille; i++)
    {

        for (int j = 0; j < compartiment; j++)
        {
            K1[j] = f.m_result_integration[j][i];
        }
        f.evaluate(K1);
        multiply_by_nbr(h, K1,compartiment);

        for (int j = 0; j < compartiment; j++)
        {
            K2[j] = f.m_result_integration[j][i] + 0.5 * K1[j];
        }
        f.evaluate(K2);
        multiply_by_nbr(h, K2,compartiment);

        for (int j = 0; j < compartiment; j++)
        {
            K3[j] = f.m_result_integration[j][i] + 0.5 * K2[j];
        }
        f.evaluate(K3);
        multiply_by_nbr(h, K3,compartiment);

        for (int j = 0; j < compartiment; j++)
        {
            K4[j] = f.m_result_integration[j][i] + K3[j];
        }
        f.evaluate(K4);
        multiply_by_nbr(h, K4,compartiment);

        for (int j = 0; j < compartiment; j++)
        {
            f.m_result_integration[j][i + 1] = f.m_result_integration[j][i] + K1[j] / 6.0 + K2[j] / 3.0 + K3[j] / 3.0 + K4[j] / 6.0;
        }

    }
    return;
}



void multiply_by_nbr(double nbr, std::vector<double> &M,int compartiment)
{
    for (int i = 0; i < compartiment; i++)
    {
        M[i] = nbr * M[i];
    }
    return;
}