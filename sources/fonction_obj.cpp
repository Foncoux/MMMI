

#include "../headers/fonction_obj.hpp"


double min_log_likelyhood_death(std::array<double,DEATH_NB_DAY> observed_data, std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data)
{
    double somme = 0;

    for(int i=0;i< DEATH_NB_DAY; i++)
    {
        somme = somme + (observed_data[i] - output_data[D_COMP][i])*(observed_data[i] - output_data[D_COMP][i])*POP_TOT;

        //std::cout << observed_data[i]*POP_TOT << " ";

        //somme = somme + ( -observed_data[i]*gsl_sf_log(output_data[D_COMP][i]) + output_data[D_COMP][i]);
    }
    //std::cout << "\n";
    return somme;
    
}

double min_log_likelyhood_hosp(std::array<double,HOSP_NB_DAY> observed_data, std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data)
{
    double somme = 0;
    int j=0;
    for(int i=DEATH_NB_DAY - HOSP_NB_DAY - 1;i< DEATH_NB_DAY; i++)
    {
        somme = somme + (observed_data[j] - output_data[Q_COMP][i])*(observed_data[j] - output_data[Q_COMP][i])*4;
        j++;
        //std::cout << output_data[D_COMP][153] << std::endl;

        //somme = somme + ( -observed_data[i]*gsl_sf_log(output_data[D_COMP][i]) + output_data[D_COMP][i]);
    }
    
    return somme;
    
}

bool minimisation(double &fct_obj, std::array<double,DEATH_NB_DAY> observed_death, std::array<double,HOSP_NB_DAY> observed_hosp, std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data)
{
    double fct_obj_temp = min_log_likelyhood_death(observed_death,output_data) + min_log_likelyhood_hosp(observed_hosp,output_data);
    
    std::cout << fct_obj << " " << fct_obj_temp << std::endl;
    if(fct_obj_temp < fct_obj)
    {
        fct_obj = fct_obj_temp;
        
        return true;
    }

    return false;
    
}

