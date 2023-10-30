
#include <array>
#include <vector>
#include <iostream>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_rng.h>

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
double log_likelyhood_death(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data)
{
    double somme = 0;
    double total_output_new,total_output_old,total_diff;
    double log;
    total_output_old = 0;
    double inter;

    for(size_t i=0;i< NB_DAY; i++)
    {
        total_output_new = 0;
        
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {               
                total_output_new = total_output_new + (output_data[classe].m_result_integration[D_COMP][i])*POP_TOT;
        }   

        total_diff = total_output_new - total_output_old;

        if( total_diff > 0){
            inter = (data.day_death[DEATH_DAY][i]*gsl_sf_log(total_diff) - total_diff);
            somme = somme + (((data.day_death[0][i]))*gsl_sf_log(total_diff) - total_diff);
        }
        total_output_old = total_output_new;
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
double log_likelyhood_hosp_week_day(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data)
{
    double somme = 0;
    double total_output;
    
    for(size_t i=0;i< NB_DAY; i++)
    {
        
        total_output = 0;
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {                           
            total_output = total_output + output_data[classe].m_result_integration[Q_ENTRY_COMP][i]*POP_TOT;
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
double log_likelyhood_recovered(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data)
{
    double somme = 0;
    double total_output;    

    total_output = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {                           
        total_output = total_output + output_data[classe].m_result_integration[R_COMP][38];
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
double log_likelyhood_death_par_day_per_age(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data)
{
    double somme = 0;
    double total_output1=0;
    double total_output2=0;
    double total_output=0;

    

    for(size_t i=1;i< NB_DAY; i++)
    {
        total_output1 = output_data[0].m_result_integration[D_COMP][i] - output_data[0].m_result_integration[D_COMP][i-1];
        total_output2 = output_data[1].m_result_integration[D_COMP][i] - output_data[1].m_result_integration[D_COMP][i-1];
        if (data.day_death_age[0][i] < 0 || data.day_death_age[1][i] < 0)
        {   
            
            total_output = total_output1 + total_output2;
            if ( total_output > 0)
            {
                somme = somme + ( data.day_death_age[2][i]*gsl_sf_log(total_output) - total_output);
               
            }
            
            
        }else
        {
             
            if (total_output1 > 1.0e-15 )
            {
                somme = somme + ( data.day_death_age[0][i]*gsl_sf_log(total_output1) - total_output1);
                
            }
            
            if (total_output2 > 1.0e-15 )
            {
                somme = somme + ( data.day_death_age[1][i]*gsl_sf_log(total_output2) - total_output2);
                
            }
        
        }
        
    }



    return somme;
}





double fonction_obj_classe_1(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data,int loglikelyhood)
{
    double result1,result2,result3,result4;
    result1 = log_likelyhood_death(data,output_data);
    result2 = - mean_square_recovered(data,output_data);
    //result3 = log_likelyhood_hosp_week(data,output_data);
    result4 = log_likelyhood_hosp_week_day(data, output_data);

    return result1 + result2 + result4;
}

/**
 * @brief Calcule -log likelyhood total
 *
 * @param data données rélles pour la calibration
 * @param output_data tableau de itérations du modèle
 * @param loglikelyhood 1 si utilisation du log likelyhood, 0 sinon
 * @return double -log likelyhood total
 */

double fonction_obj(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data,int loglikelyhood)
{
    double result,result1,result2,result3,result4,result5,result6,result7,result8,result9;
    if(loglikelyhood == 1){
        if (NB_CLASSE_AGE == 2)
        {
            //result1 = log_likelyhood_death(data,output_data)/295;
            //result2 = log_likelyhood_recovered(data,output_data);
            //result3 = log_likelyhood_hosp(data,output_data);
            //result4 = log_likelyhood_death_month2(data,output_data)/9;
            //result5 = (log_likelyhood_hosp_week(data,output_data));
            //result6 = log_likelyhood_recovered_ages2(data,output_data);
            //result8 = log_likelyhood_death_par_day_per_age(data,output_data);
            //result9 = log_likelyhood_infect(data,output_data)/295;
            //result = result8 + result2 + result3 /*+ result4*/ + result5 + result6;// + result9;
            //
            //result7 = 1000; 
            //std::cout << min_log_likelyhood_death(data,output_data)/295 << "  " << min_log_likelyhood_recovered(data,output_data) << "  " << min_log_likelyhood_hosp(data,output_data)/58 << "   " << min_log_likelyhood_death_month2(data,output_data)/9 << "  " << min_log_likelyhood_hosp_week(data,output_data)/42 << "  " << min_log_likelyhood_recovered_ages2(data,output_data) << "  " ;
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


double mean_square_recovered(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data)
{
    double total_output;
    double somme2=0;
    
    total_output = 0;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {                           
        total_output = total_output + output_data[classe].m_result_integration[R_COMP][38];
    }   
    
    total_output = total_output;

    if (total_output < (2.1/100) || total_output > (3.7/100))
    {   
        somme2 = somme2 + ((2.8/100) - total_output)*((2.8/100) - total_output)*10000000000;
        
    }


        
    return somme2;
}
