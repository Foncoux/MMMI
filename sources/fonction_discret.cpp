#include <array>
#include <iostream>
#include <gsl/gsl_rng.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"
#include "../headers/fonction_discret.hpp"

/**
 * @brief permet d'appliquer la blackbox avec le modèle en temps discret pour plusieurs classe d'age
 * 
 * @param f tableau de fonction discrete. Modifiée en sortie de fonction.
 * @param p tableau de structure parametres pour la fonction f.
 * @param data données réelles pour la calibration.
 */

int bb_discret(std::array<ODE,NB_CLASSE_AGE>& f,std::array<parametres,NB_CLASSE_AGE> p,const Data &data)
{   
    //print_parameter(p);
    int output_model;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        p[classe].i=0;
    }
    
    
    
    double lambda;
    for (int n = 0; n < NB_DAY-1; n++)
    {           
        if(std::find(TAB_DATE_CONFINEMENT.begin(), TAB_DATE_CONFINEMENT.end(), n) != TAB_DATE_CONFINEMENT.end()){
            for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
            {
                p[classe].i++;
            }
        }

        for (size_t i = 0; i < NB_CLASSE_AGE; i++)
        {
            lambda = force_infection_classe(n,i,f,data);
            output_model = f[i].m_function_discret(f[i].m_result_integration,p[i],n,lambda);
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
int SIRQD_discret(std::array<std::array<double, T_FINAL>, COMPARTIMENT> &y,parametres p,int n,double lambda)
{

    //std::cout << lambda << std::endl;


    y[S_COMP][n+1] = y[S_COMP][n] - p.beta[p.i]*lambda*y[S_COMP][n];
    y[I_COMP][n+1] = y[I_COMP][n] + p.beta[p.i]*lambda*y[S_COMP][n] - (p.delta+p.gamma)*y[I_COMP][n];
    y[R_COMP][n+1] = y[R_COMP][n] + p.gamma*y[I_COMP][n] + p.eps*y[Q_COMP][n];
    y[Q_COMP][n+1] = y[Q_COMP][n] + p.delta*y[I_COMP][n] - (p.eps + p.r)*y[Q_COMP][n];
    y[D_COMP][n+1] = y[D_COMP][n] + p.r*y[Q_COMP][n];


    //https://academic.oup.com/cid/article/74/9/1678/6359063
/*
    y[S_COMP][n+1] = y[S_COMP][n] - p.beta[p.i]*lambda*y[S_COMP][n];
    y[E_COMP][n+1] = y[E_COMP][n] + p.beta[p.i]*lambda*y[S_COMP][n] - (p.sigma)*y[E_COMP][n];
    y[I_COMP][n+1] = y[I_COMP][n] - (p.delta+p.gamma)*y[I_COMP][n] + (p.sigma)*y[E_COMP][n];
    y[R_COMP][n+1] = y[R_COMP][n] + p.gamma*y[I_COMP][n] + p.eps*y[Q_COMP][n];
    y[Q_COMP][n+1] = y[Q_COMP][n] + p.delta*y[I_COMP][n] - (p.eps + p.r)*y[Q_COMP][n];
    y[D_COMP][n+1] = y[D_COMP][n] + p.r*y[Q_COMP][n];
*/

/*
    y[S_COMP][n+1] = y[S_COMP][n] - p.beta[p.i]*lambda*y[S_COMP][n];
    y[E_COMP][n+1] = y[E_COMP][n] + p.beta[p.i]*lambda*y[S_COMP][n] - (p.sigma)*y[E_COMP][n] - (p.sigma_A)*y[E_COMP][n];
    y[A_COMP][n+1] = y[A_COMP][n] + (p.sigma_A)*y[E_COMP][n] - p.gamma_A*y[A_COMP][n];
    y[I_COMP][n+1] = y[I_COMP][n] - (p.delta+p.gamma)*y[I_COMP][n] + (p.sigma)*y[E_COMP][n];
    y[R_COMP][n+1] = y[R_COMP][n] + p.gamma*y[I_COMP][n] + p.eps*y[Q_COMP][n] + p.gamma_A*y[I_COMP][n];
    y[Q_COMP][n+1] = y[Q_COMP][n] + p.delta*y[I_COMP][n] - (p.eps + p.r)*y[Q_COMP][n];
    y[D_COMP][n+1] = y[D_COMP][n] + p.r*y[Q_COMP][n];
*/
    /*
    for (size_t i = 0; i < 4; i++)
    {
        std::cout << p.beta[i] << "  " << lambda << "  " << p.beta[i]*lambda << "  \n" << std::endl;
    }
    */

    if (p.beta[p.i]*lambda > 1)
    {
        //std::cout <<  "!!! p.beta[i]*lambda > 1 !!!" << "  \n" << std::endl;
        return -1;
    }
    
    
    //std::cout << y[S_COMP][n+1] << " " << y[I_COMP][n+1] << " " << y[R_COMP][n+1] << " " << y[Q_COMP][n+1] << " " << y[D_COMP][n+1] << std::endl;
    

    if(y[S_COMP][n+1] < 0 || y[I_COMP][n+1] < 0 || y[R_COMP][n+1] < 0 || y[Q_COMP][n+1] < 0 || y[D_COMP][n+1] < 0 || y[E_COMP][n+1] < 0 )
    {
        std::cout << "\n output negatifs \n" << std::endl;
        //return -2;
        exit(0);
    }

    return 0;
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
double force_infection_classe(int jour,int classe_age,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data) 
{
    
    double result=0;
    //std::cout << "next ite" << std::endl;
    for (size_t j = 0; j < NB_CLASSE_AGE; j++){
        result = result + data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[I_COMP][jour] /*+ 0.51*data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[A_COMP][jour]*/ ;
        
//        std::cout << "force : " << data.social_contact_matrix[classe_age][j] ;
//        std::cout << "  " << f[j].m_result_integration[I_COMP][jour] ;
//        std::cout << "  " << result << std::endl;
    }
    //std::cout << data.social_constact_matrix[classe_age][0] << std::endl;
    
    return result;

}




/*
void SEIRQD_discret(std::array<std::array<double, T_FINAL>, COMPARTIMENT> &y,parametres p,int n,double lambda)
{

    //std::cout << lambda << std::endl;

    y[S_COMP][n+1] = y[S_COMP][n] - p.beta[p.i]*lambda*y[S_COMP][n];
    y[E_COMP][n+1] = y[E_COMP][n] + p.beta[p.i]*lambda*y[S_COMP][n];
    y[I_COMP][n+1] = y[I_COMP][n] + p.beta[p.i]*lambda*y[S_COMP][n] - (p.delta+p.gamma)*y[I_COMP][n];
    y[R_COMP][n+1] = y[R_COMP][n] + p.gamma*y[I_COMP][n] + p.eps*y[Q_COMP][n];
    y[Q_COMP][n+1] = y[Q_COMP][n] + p.delta*y[I_COMP][n] - (p.eps + p.r)*y[Q_COMP][n];
    y[D_COMP][n+1] = y[D_COMP][n] + p.r*y[Q_COMP][n];




    if(y[S_COMP][n+1] < 0 || y[I_COMP][n+1] < 0 || y[R_COMP][n+1] < 0 || y[Q_COMP][n+1] < 0 || y[D_COMP][n+1] < 0 )
    {
        std::cout << "\n \n \n \n output negatifs \n \n \n \n" << std::endl;
    }

    if((y[S_COMP][n+1] + y[I_COMP][n+1] + y[R_COMP][n+1] + y[Q_COMP][n+1] + y[D_COMP][n+1] -1) > 0.0000000001 || (y[S_COMP][n+1] + y[I_COMP][n+1] + y[R_COMP][n+1] + y[Q_COMP][n+1] + y[D_COMP][n+1] -1) < -0.00000000001)
    {
        std::cout << "\n \n \n \n population non constante :  \n \n \n \n" << y[S_COMP][n+1] + y[I_COMP][n+1] + y[R_COMP][n+1] + y[Q_COMP][n+1] + y[D_COMP][n+1] -1 << std::endl;
    }

}
*/