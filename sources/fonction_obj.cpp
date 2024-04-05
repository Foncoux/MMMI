#include <array>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>
#include <math.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"

#include "../headers/Data.hpp"
#include "../headers/fonction_obj.hpp"



/**
 * @brief Calcule -log likelyhood relative aux morts par âges
 * 
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @return double -log likelyhood relative au mort totales
 */
double log_likelyhood_death(ODE& output_data)
{
    double somme = 0;
    
    double total_output;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        for (size_t day = 0; day < NB_DAY_CALIBRATION; day++)
        {
            total_output = output_data.m_result_simulation[classe][D_ENTRY_COMP][day]*POP_TOT;
            
            if( total_output > 0){
                somme = somme + (((DATA.day_death[classe][day]))*gsl_sf_log(total_output) - total_output);
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

double log_likelyhood_hosp(ODE& output_data)
{
    double somme = 0;
    
    double total_output;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        
        for (size_t day = 0; day < NB_DAY_CALIBRATION; day++)
        {
            total_output = output_data.m_result_simulation[classe][Q_ENTRY_COMP][day]*POP_TOT;
            
            if( total_output > 0){
                somme = somme + (((DATA.day_hosp[classe][day]))*gsl_sf_log(total_output) - total_output);
            }


        }
    }

    return somme;
}



/**
 * @brief Calcule -log likelyhood total
 *
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @param loglikelyhood 1 si utilisation du log likelyhood, 0 sinon
 * @return double -log likelyhood total
 */

double fonction_obj(ODE& output_data)
{
    double result,result1,result2,result3;
    
    result1 = log_likelyhood_death(output_data);
    result3 = log_likelyhood_hosp(output_data);

    switch (NB_CLASSE_AGE)
    {
    case 1:
        result2 = - least_square_recovered_1(output_data);
        break;
    
    case 2:
        result2 = - least_square_recovered_2(output_data);
        break;

    case 4:
        result2 = - least_square_recovered_4(output_data);
        break;

    case 8:
        result2 = - least_square_recovered_8(output_data);
        break;

    default:
        break;
    }

    result = result1 + result2 + result3;
    return result;

}




double least_square_recovered_1(ODE& output_data)
{
    double total_output;
    double somme2=0;
    
    total_output = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {                           
        total_output = total_output + output_data.m_result_simulation[classe][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    }   
    

    if (total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + sqrt(((2.8/100) - total_output)*((2.8/100) - total_output))*1000000000000;
        
    }


        
    return somme2;
}



double least_square_recovered_2(ODE& output_data)
{
    double total_output;
    double somme2=0;
    
    total_output = 0;
   
    total_output = output_data.m_result_simulation[0][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (0.6/100) || total_output > (7.5/100))
    {   
        somme2 = somme2 + sqrt(((4.05/100) - total_output)*((4.05/100) - total_output))*10000000;
    }

    total_output = output_data.m_result_simulation[1][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (1.2/100) || total_output > (5.1/100))
    {   
        somme2 = somme2 + sqrt(((2.5/100) - total_output)*((2.5/100) - total_output))*10000000;
    }    

    total_output = output_data.m_result_simulation[0][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY] + output_data.m_result_simulation[1][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + sqrt(((2.8/100) - total_output)*((2.8/100) - total_output))*10000000;
    }
    

        
    return somme2;
}



double least_square_recovered_4(ODE& output_data)
{
    double total_output=0, somme2=0;
   
    
    total_output = output_data.m_result_simulation[0][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (0.6/100) || total_output > (4.9/100))
    {   
        somme2 = somme2 + sqrt(((1.7/100) - total_output)*((1.7/100) - total_output))*10000000;
    }

    
    total_output = output_data.m_result_simulation[1][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (3.2/100) || total_output > (7.5/100))
    {   
        somme2 = somme2 + sqrt(((4.9/100) - total_output)*((4.9/100) - total_output))*10000000;
    }



    total_output = output_data.m_result_simulation[2][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (1.2/100) || total_output > (3.2/100))
    {   
        somme2 = somme2 + sqrt(((1.9/100) - total_output)*((1.9/100) - total_output))*10000000;
    }


    
    total_output = output_data.m_result_simulation[3][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (1.2/100) || total_output > (5.1/100))
    {   
        somme2 = somme2 + sqrt(((2.5/100) - total_output)*((2.5/100) - total_output))*10000000;
    }


    total_output = 0;
    for (size_t i = 0; i < 4; i++)
    {
        total_output = total_output + output_data.m_result_simulation[i][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    }
    if(total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + sqrt(((2.8/100) - total_output)*((2.8/100) - total_output))*10000000;
    }
    
    
    return somme2;
}




double least_square_recovered_8(ODE& output_data)
{
    double total_output=0, somme2=0;
   
    
    total_output = output_data.m_result_simulation[0][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (0.6/100) || total_output > (4.9/100))
    {   
        somme2 = somme2 + sqrt(((1.7/100) - total_output)*((1.7/100) - total_output))*10000000;
    }

    
    total_output = output_data.m_result_simulation[1][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (3.2/100) || total_output > (7.5/100))
    {   
        somme2 = somme2 + sqrt(((4.9/100) - total_output)*((4.9/100) - total_output))*10000000;
    }



    total_output = output_data.m_result_simulation[2][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY] + output_data.m_result_simulation[3][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY] + output_data.m_result_simulation[4][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (1.2/100) || total_output > (3.2/100))
    {   
        somme2 = somme2 + sqrt(((1.9/100) - total_output)*((1.9/100) - total_output))*10000000;
    }



    total_output = output_data.m_result_simulation[5][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY] + output_data.m_result_simulation[6][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY] + output_data.m_result_simulation[7][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    if(total_output < (1.2/100) || total_output > (5.1/100))
    {   
        somme2 = somme2 + sqrt(((2.5/100) - total_output)*((2.5/100) - total_output))*10000000;
    }


    total_output = 0;
    for (size_t i = 0; i < 8; i++)
    {
        total_output = total_output + output_data.m_result_simulation[i][R_COMP][DAY_SEROLOGY - DELAY_DAY_SEROLOGY];
    }
    if(total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + sqrt(((2.8/100) - total_output)*((2.8/100) - total_output))*10000000;
    }
    
    
    return somme2;
}

