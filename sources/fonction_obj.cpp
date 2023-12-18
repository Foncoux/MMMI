
#include <array>
#include <vector>
#include <iostream>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>
#include <math.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_obj.hpp"



/**
 * @brief Calcule -log likelyhood relative aux morts totales
 * 
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @return double -log likelyhood relative au mort totales
 */
double log_likelyhood_death(const Data &data, ODE& output_data)
{
    double somme = 0;
    double total_output;

    for(size_t i=0;i< NB_DAY_CALIBRATION; i++)
    {
        total_output= 0;
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {               
                total_output = total_output + (output_data.m_result_simulation[classe][D_ENTRY_COMP][i])*POP_TOT;
        }   

        if( total_output > 0){
            
            somme = somme + (((data.day_death[0][i]))*gsl_sf_log(total_output) - total_output);
        }
    }    
    
    return somme;
}

/**
 * @brief Calcule -log likelyhood relative aux hospitalisations totales
 * 
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @return double -log likelyhood relative aux hospitalisations totales
 */
double log_likelyhood_hosp_week_day(const Data &data, ODE& output_data)
{
    double somme = 0;
    double total_output;
    
    for(size_t i=0;i< NB_DAY_CALIBRATION; i++)
    {
        
        total_output = 0;
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {                           
            total_output = total_output + output_data.m_result_simulation[classe][Q_ENTRY_COMP][i]*POP_TOT;
        }   

        if( total_output > 0){
            somme = somme + ( ((data.day_hosp[0][i]))*gsl_sf_log(total_output) - total_output);  
        }

    }

    
    return somme;
}

/**
 * @brief Calcule -log likelyhood relative aux rétabils totaux
 * 
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @return double -log likelyhood relative aux rétabils totaux
 */
double log_likelyhood_recovered(const Data &data, ODE& output_data)
{
    double somme = 0;
    double total_output;    

    total_output = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {                           
        total_output = total_output + output_data.m_result_simulation[classe][R_COMP][38];
    }   
    
    if( total_output > 0){

        if (total_output < (2.1/100) || total_output > (3.7/100))
        {   
            somme = somme + ( (2.8/100)*gsl_sf_log(total_output) - total_output)*1000000000;
            
        }
    }
        
    return somme;
}






/**
 * @brief Calcule -log likelyhood relative aux morts par âges
 * 
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @return double -log likelyhood relative au mort totales
 */
double log_likelyhood_death_par_day_per_age(const Data &data, ODE& output_data)
{
    double somme = 0;
    
    double total_output;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        for (size_t day = 0; day < NB_DAY_CALIBRATION; day++)
        {
            total_output = output_data.m_result_simulation[classe][D_ENTRY_COMP][day]*POP_TOT;
            
            if( total_output > 0){
                somme = somme + (((data.day_death[classe][day]))*gsl_sf_log(total_output) - total_output);
            }

        }
    }

    return somme;
    
}



/**
 * @brief Calcule -log likelyhood relative aux morts par âges
 * 
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @return double -log likelyhood relative au mort totales
 */

double log_likelyhood_hosp_par_day_per_age(const Data &data, ODE& output_data)
{
    double somme = 0;
    
    double total_output;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        
        for (size_t day = 0; day < NB_DAY_CALIBRATION; day++)
        {
            total_output = output_data.m_result_simulation[classe][Q_ENTRY_COMP][day]*POP_TOT;
            
            if( total_output > 0){
                somme = somme + (((data.day_hosp[classe][day]))*gsl_sf_log(total_output) - total_output);
            }


        }
    }

    return somme;
}




double fonction_obj_classe_1(const Data &data, ODE& output_data,int loglikelyhood)
{
    double result1,result2,result3,result4;
    result1 = log_likelyhood_death(data,output_data);
    result2 = - mean_square_recovered(data,output_data);
    //result3 = log_likelyhood_hosp_week(data,output_data);
    result4 = log_likelyhood_hosp_week_day(data, output_data);

    double result = result1 + result2 + result4;
    return result;
}

double fonction_obj_classe_2(const Data &data, ODE& output_data,int loglikelyhood)
{
    double result1,result2,result3;
    result1 = log_likelyhood_death_par_day_per_age(data, output_data);
    result2 = - mean_square_recovered_classe2(data, output_data);
    result3 = log_likelyhood_hosp_par_day_per_age(data, output_data);


    return result1 +result2+ result3;
}

/**
 * @brief Calcule -log likelyhood total
 *
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @param loglikelyhood 1 si utilisation du log likelyhood, 0 sinon
 * @return double -log likelyhood total
 */

double fonction_obj(const Data &data, ODE& output_data,int loglikelyhood)
{
    double result,result1,result2,result3,result4,result5,result6,result7,result8,result9;
    if(loglikelyhood == 1){
        if (NB_CLASSE_AGE == 2)
        {
            result =  fonction_obj_classe_2(data, output_data, loglikelyhood);
            
        }else
        {
            result =  fonction_obj_classe_1(data, output_data, loglikelyhood);

        }
        

    }else
    {
        //result = min_square_death(data,output_data) + min_square_recovered(data,output_data) + min_square_hosp(data,output_data)*10 + min_square_infect(data,output_data)/10000;

    }
    //std::cout << min_log_likelyhood_death(data,output_data)/NB_DAY << "    " << min_log_likelyhood_recovered(data,output_data) << "   ";

    //std::cout << min_log_likelyhood_death(data,output_data) << "  " << min_log_likelyhood_recovered(data,output_data) << "  " << min_log_likelyhood_hosp(data,output_data) << "  " << min_log_likelyhood_infect(data,output_data) << "  "; 
    return result;

}


double mean_square_recovered(const Data &data, ODE& output_data)
{
    double total_output;
    double somme2=0;
    
    total_output = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {                           
        total_output = total_output + output_data.m_result_simulation[classe][R_COMP][38];
    }   
    
    total_output = total_output;

    if (total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + ((2.8/100) - total_output)*((2.8/100) - total_output)*1000000000000;
        
    }


        
    return somme2;
}

double mean_square_recovered_classe2(const Data &data, ODE& output_data)
{
    double total_output;
    double somme2=0;
    
    total_output = 0;
   
    total_output = output_data.m_result_simulation[0][R_COMP][38];
    if(total_output < (0.6/100) || total_output > (7.5/100))
    {   
        somme2 = somme2 + sqrt(((4.05/100) - total_output)*((4.05/100) - total_output))*10000000;
    }

    total_output = output_data.m_result_simulation[1][R_COMP][38];
    if(total_output < (1.2/100) || total_output > (5.1/100))
    {   
        somme2 = somme2 + sqrt(((2.5/100) - total_output)*((2.5/100) - total_output))*10000000;
    }    

    total_output = output_data.m_result_simulation[0][R_COMP][38] + output_data.m_result_simulation[1][R_COMP][38];
    if(total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + sqrt(((2.8/100) - total_output)*((2.8/100) - total_output))*10000000;
    }
    

        
    return somme2;
}