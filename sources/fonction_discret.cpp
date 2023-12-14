#include <array>
#include <vector>
#include <iostream>
#include <gsl/gsl_rng.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_discret.hpp"
#include "../headers/fonction_continuous.hpp"


int model(ODE& f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> &param_opti,const Data &data)
{
    set_condition_initiale(f,param_opti);
    
    return bb_discret_new(f,param_opti,data);
}



/**
 * @brief calcule la force d'infection pour un classe d'age donnée et un jour particulier
 * 
 * @param jour 
 * @param classe_age 
 * @param f 
 * @param data 
 * @return double 
 */
double force_infection_classe(int jour,int classe_age,ODE& f,const Data &data) 
{
    
    double result=0;
    for (size_t j = 0; j < NB_CLASSE_AGE; j++){
        result = result + SOCIAL_CONTACT_MATRIX[classe_age][j]*(f.m_result_simulation[classe_age][I_COMP][jour]) /*+ 0.51*data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[A_COMP][jour]*/ ;
    }
    
    return result;

}


/**
 * @brief permet d'appliquer la blackbox avec le modèle en temps discret pour plusieurs classe d'age
 * 
 * @param f tableau de fonction discrete. Modifiée en sortie de fonction.
 * @param p tableau de structure parametres pour la fonction f.
 * @param data données réelles pour la calibration.
 */

int bb_discret_new(ODE& f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,const Data &data)
{   
    int output_model;
    double confinement = 0;
    
    double lambda;
    for (int jour = 0; jour < NB_DAY-1; jour++)
    {           
        if(std::find(TAB_DATE_CONFINEMENT.begin(), TAB_DATE_CONFINEMENT.end(), jour) != TAB_DATE_CONFINEMENT.end()){
            confinement++;
        }

        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            lambda = force_infection_classe(jour,classe,f,data);
            output_model = f.m_function_discret_new(f.m_result_simulation[classe],p,jour,lambda,classe,confinement);
            if(output_model != 0){
                return output_model;
            }    
        }

    }
    return 0;
}



/**
 * @brief caclule l'itération n+1 du modèle SIRQD
 * 
 * @param y tableau 2D contenant toutes les itérations du modèle. Modifié en sortie de fonction
 * @param p parametres pour le modèle
 * @param n entier n pour connaitre l'itération
 * @param lambda force d'infection
 */

int SIRQD_discret_new(std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT> &y,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,int n,double lambda, int classe, int confinement)
{

    //std::cout << lambda << std::endl;
    double delta = p[NB_PARAM_TOT*classe + PARAM_ID_DELTA];
    double gamma = p[NB_PARAM_TOT*classe + PARAM_ID_GAMMA];
    double eps = p[NB_PARAM_TOT*classe + PARAM_ID_EPS];
    double r = p[NB_PARAM_TOT*classe + PARAM_ID_R];

    double beta = p[NB_PARAM_TOT*classe + NB_PARAM + confinement];

    y[S_COMP][n+1] = y[S_COMP][n] - beta*lambda*y[S_COMP][n];
    y[I_COMP][n+1] = y[I_COMP][n] + beta*lambda*y[S_COMP][n] - (delta+gamma)*y[I_COMP][n];
    y[R_COMP][n+1] = y[R_COMP][n] + gamma*y[I_COMP][n] + eps*y[Q_COMP][n];
    y[Q_COMP][n+1] = y[Q_COMP][n] + delta*y[I_COMP][n] - (eps + r)*y[Q_COMP][n];
    y[D_COMP][n+1] = y[D_COMP][n] + r*y[Q_COMP][n];
    y[Q_ENTRY_COMP][n+1] = delta*y[I_COMP][n];
    y[D_ENTRY_COMP][n+1] = r*y[Q_COMP][n];


    if (beta*lambda > 1)
    {
        //std::cout <<  "!!! p.beta[i]*lambda > 1 !!!" << "  \n" << std::endl;
        return -1;
    }
    
    
    //std::cout << y[S_COMP][n+1] << " " << y[I_COMP][n+1] << " " << y[R_COMP][n+1] << " " << y[Q_COMP][n+1] << " " << y[D_COMP][n+1] << std::endl;
    

    if(y[S_COMP][n+1] < 0 || y[I_COMP][n+1] < 0 || y[R_COMP][n+1] < 0 || y[Q_COMP][n+1] < 0 || y[D_COMP][n+1] < 0)

    {
        std::cout << "\n output negatifs \n" << std::endl;
        //return -2;
        exit(0);
    }

    return 0;
}



