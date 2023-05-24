

#include "../headers/fonction_obj.hpp"

void set_condition_initiale(double y[],std::array<std::array<std::array<double, T_FINAL>, COMPARTIMENT>, NB_CLASSE_AGE> &model_result) /////////////////////////////////////////////
{////////////////////////////////////////////////////////////
    model_result[0][0][0] = y[0];
    model_result[0][1][0] = y[1];
    model_result[0][2][0] = y[2];
    model_result[0][3][0] = y[3];
    model_result[0][4][0] = y[4];
}

double min_log_likelyhood_death(std::array<double,DEATH_NB_DAY> observed_data, ODE output_data[])
{
    double somme = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
    
        for(int i=0;i< DEATH_NB_DAY; i++)
        {
            //somme = somme + (observed_data[i] - output_data[D_COMP][i])*(observed_data[i] - output_data[D_COMP][i])*POP_TOT;
            double output = output_data[classe].m_result_integration[D_COMP][i];
            if( output > 0.0000000000000001){
                somme = somme + ( -observed_data[i]*gsl_sf_log(output) + output)*POP_TOT;
            }
            
            
        }
    }
    //std::cout << "\n";
    return somme;
    
}

double min_log_likelyhood_hosp(std::array<double,HOSP_NB_DAY> observed_data, ODE output_data[])
{
    double somme = 0;
    int j=0;
    
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {

        for(int i=DEATH_NB_DAY - HOSP_NB_DAY - 1;i< DEATH_NB_DAY; i++)
        {
            //somme = somme + (observed_data[j] - output_data[Q_COMP][i])*(observed_data[j] - output_data[Q_COMP][i])*4;
            
            //std::cout << output_data[D_COMP][153] << std::endl;
        
        
            double output = output_data[classe].m_result_integration[Q_COMP][i];

            if(output > 0.000000000000001){
                somme = somme + ( -observed_data[j]*gsl_sf_log(output) + output);
            }
            j++;
        }
    }
    return somme;
    
}

double fonction_obj(std::array<double,DEATH_NB_DAY> observed_death, std::array<double,HOSP_NB_DAY> observed_hosp, ODE output_data[])
{
    return min_log_likelyhood_death(observed_death,output_data) /*+ min_log_likelyhood_hosp(observed_hosp,output_data)*/;
}

bool minimisation(double &fct_obj, std::array<double,DEATH_NB_DAY> observed_death, std::array<double,HOSP_NB_DAY> observed_hosp, ODE output_data[])
{
    

    double fct_obj_temp = fonction_obj(observed_death, observed_hosp, output_data);
    
    

    std::cout << fct_obj << " " << fct_obj_temp << std::endl;

    if(fct_obj_temp < fct_obj)
    {
        fct_obj = fct_obj_temp;
        
        return true;
    }

    return false;
    
}

