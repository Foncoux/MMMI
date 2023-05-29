

#include "../headers/fonction_obj.hpp"



double min_log_likelyhood_death(const Data &data, ODE output_data[])
{
    double somme = 0;
    double total_output;

    for(size_t i=0;i< NB_DAY; i++)
    {
        total_output = 0;

        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {               
            if (i!=0)
            {
                total_output = total_output + (output_data[classe].m_result_integration[D_COMP][i]);
            }else{total_output = total_output + output_data[classe].m_result_integration[D_COMP][i];}           
        }   
        //somme = somme + (data.day_all[DEATH_DAY][i] - total_output)*(data.day_all[DEATH_DAY][i] - total_output);
        //std::cout << total_output*POP_TOT << "  " << data.day_all[DEATH_DAY][i]*POP_TOT << std::endl;
        
        if( total_output > 0.0000000000000001){
                somme = somme + ( -data.day_all[DEATH_DAY][i]*gsl_sf_log(total_output) + total_output);
        }
        
    }

    return somme;
}



double min_log_likelyhood_hosp(const Data &data, ODE output_data[])
{
    double somme = 0;
    double total_output;

    for(size_t i=HOSP_DEBUT;i< NB_DAY; i++)
    {
        total_output = 0;
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {                           
            total_output = total_output + output_data[classe].m_result_integration[Q_COMP][i];
        }   
        
        if( total_output > 0.0000000000000001){
                somme = somme + ( -data.day_all[HOSP_DAY][i]*gsl_sf_log(total_output) + total_output);
        }
        
    }
    
    return somme;
}

double min_log_likelyhood_infect(const Data &data, ODE output_data[])
{
    double somme = 0;
    double total_output;

    for(size_t i=0;i< NB_DAY; i++)
    {
        total_output = 0;
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {                           
            total_output = total_output + output_data[classe].m_result_integration[I_COMP][i];
        }   
        
        if( total_output > 0.0000000000000001){
            if (total_output < data.day_all[PREV_LOW_DAY][i] || total_output > data.day_all[PREV_HIGH_DAY][i])
            {   
                somme = somme + ( -data.day_all[PREV_MEDIUM_DAY][i]*gsl_sf_log(total_output) + total_output);
            }
            
               
        }
        
    }
    
    return somme;
}


double fonction_obj(const Data &data, ODE output_data[])
{
    return (min_log_likelyhood_death(data,output_data)/NB_DAY)*10 + min_log_likelyhood_hosp(data,output_data)/(NB_DAY-HOSP_DEBUT) /*+ min_log_likelyhood_infect(data,output_data)/NB_DAY*/;
}

bool minimisation(double &fct_obj, const Data &data, ODE output_data[])
{
    

    double fct_obj_temp = fonction_obj(data, output_data);
    
    

    std::cout << fct_obj << " " << fct_obj_temp << std::endl;

    if(fct_obj_temp < fct_obj)
    {
        fct_obj = fct_obj_temp;
        
        return true;
    }

    return false;
    
}

