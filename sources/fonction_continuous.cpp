
#include <algorithm>
#include <array>
#include <vector>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_rng.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/fonction_continuous.hpp"



int model_SIRQD(double t, const double y[], double f[],void *params){   

    (void)(t);
    std::array<parametres, NB_CLASSE_AGE> *p = reinterpret_cast<std::array<parametres, NB_CLASSE_AGE> *>(params);
    //parametres *p = reinterpret_cast<parametres *>(params);

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {

        double lambda=0;
        for (size_t j = 0; j < NB_CLASSE_AGE; j++){
            lambda = lambda + SOCIAL_CONTACT_MATRIX[classe][j]*y[classe*NB_CLASSE_AGE + I_COMP] /*+ 0.51*data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[A_COMP][jour]*/ ;
        }

        f[classe*NB_CLASSE_AGE + S_COMP] = -(*p)[classe].beta[(*p)[classe].i]*lambda*y[classe*NB_CLASSE_AGE + S_COMP];
        f[classe*NB_CLASSE_AGE + I_COMP] = (*p)[classe].beta[(*p)[classe].i]*y[classe*NB_CLASSE_AGE + S_COMP]*y[classe*NB_CLASSE_AGE + I_COMP] - ((*p)[classe].delta+(*p)[classe].gamma)*y[classe*NB_CLASSE_AGE + I_COMP];
        f[classe*NB_CLASSE_AGE + R_COMP] = (*p)[classe].gamma*y[classe*NB_CLASSE_AGE + I_COMP] + (*p)[classe].eps*y[classe*NB_CLASSE_AGE + Q_COMP];
        f[classe*NB_CLASSE_AGE + Q_COMP] = (*p)[classe].delta*y[classe*NB_CLASSE_AGE + I_COMP] - ((*p)[classe].eps + (*p)[classe].r)*y[classe*NB_CLASSE_AGE + Q_COMP];
        f[classe*NB_CLASSE_AGE + D_COMP] = (*p)[classe].r*y[classe*NB_CLASSE_AGE + Q_COMP];
    
        
        
    }
    return GSL_SUCCESS;

}

void integrate(std::array<ODE,NB_CLASSE_AGE>& f,std::array<parametres,NB_CLASSE_AGE>  p, double y[])
{
    
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        p[classe].i=0;
    }

    gsl_odeiv2_system sys = {f[0].m_function, f[0].m_jacobian, COMPARTIMENT*NB_CLASSE_AGE, &p};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, 1e-2, 1e-6, 1e-4);

    double t = T_DEBUT;

    for (int i = 1; i < T_FINAL; i++)
    {
        if(std::find(TAB_DATE_CONFINEMENT.begin(), TAB_DATE_CONFINEMENT.end(), i) != TAB_DATE_CONFINEMENT.end()){
            for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
            {
                p[classe].i++;
            }
        }
        
        double ti = (double)i;
        
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        //printf ("%.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4]);

        if (status != GSL_SUCCESS)
        {
            printf ("error, return value=%d\n", status);
            break;
        }

        
        write_result_conversion_vector_to_ODE(f, y, i);

//        f.m_result_integration[0][i] = y[0];
//        f.m_result_integration[1][i] = y[1];

//        f.m_result_integration[2][i] = y[2];
//        f.m_result_integration[3][i] = y[3];
//        f.m_result_integration[4][i] = y[4];

       

    }



    gsl_odeiv2_driver_free (d);
}


void write_result_conversion_ODE_to_vector(std::array<ODE,NB_CLASSE_AGE>& f, double y[],int jour)
{
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        for (size_t compartiment = 0; compartiment < COMPARTIMENT; compartiment++)
        {
            y[classe*COMPARTIMENT + compartiment] = f[classe].m_result_integration[compartiment][jour];
        }
        
    }
    
}



void write_result_conversion_vector_to_ODE(std::array<ODE,NB_CLASSE_AGE>& f, double y[],int jour)
{
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        for (size_t compartiment = 0; compartiment < COMPARTIMENT; compartiment++)
        {
            f[classe].m_result_integration[compartiment][jour] = y[classe*COMPARTIMENT + compartiment];
        }
        
    }
    
}








int oscillateur_harm(double t, const double y[], double f[],void *params)
{
    (void)(t); /* avoid unused parameter warning */
    //(void)(params);
    f[0] = y[1];
    f[1] = -y[0];

    return GSL_SUCCESS;

}

int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    (void)(t); /* avoid unused parameter warning */
    (void)(params);
    (void)(y);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix * m = &dfdy_mat.matrix;
    gsl_matrix_set (m, 0, 0, 0.0); //valeur de l'élément #include "../config/config.hpp"(0,0) de la jacobienne
    gsl_matrix_set (m, 0, 1, 1.0);//valeur de l'élément (0,1) de la jacobienne
    gsl_matrix_set (m, 1, 0, - 1.0); //valeur de l'élément (1,0) de la jacobienne
    gsl_matrix_set (m, 1, 1, 0.0); //valeur de l'élément (1,1) de la jacobienne

    dfdt[0] = 0.0; // valeur de la dérivée de l'équation 1 par rapport à t
    dfdt[1] = 0.0; // valeur de la dérivée de l'équation 2 par rapport à t
    return GSL_SUCCESS;
}




/*
BUT     : appliquer la fonction SIRQD (sur la période 1 mars au 3 mai avec confinement le 18 mars), SIRQD étant le modèle utiliser pour modéliser l'épidémie.
INPUT   : - a : un pointeur vers un tableau 5x1 (créé dynamiquement) contenant des doubles.
          - p : structure contenant les paramètres de l'épidémie.
          - jour : entier > 0. (permettant de savoir quand le parmètre p.beta2 va être sollicité).
MODIFIES: - a : application de la fonction SIRQD et écriture du résultat.
OUTPUT  : /
*/
/*
int model_SIRQD(double t, const double y[], double f[],void *params)
{
    
        (void)(t);

        parametres *p = reinterpret_cast<parametres *>(params);
        
        f[S_COMP] = -p->beta[p->i]*y[S_COMP]*y[I_COMP];
        f[I_COMP] = p->beta[p->i]*y[S_COMP]*y[I_COMP] - (p->delta+p->gamma)*y[I_COMP];
        f[R_COMP] = p->gamma*y[I_COMP] + p->eps*y[Q_COMP];
        f[Q_COMP] = p->delta*y[I_COMP] - (p->eps + p->r)*y[Q_COMP];
        f[D_COMP] = p->r*y[Q_COMP];
    
        
        return GSL_SUCCESS;
}
*/

int jacobian_SIRQD(double t, const double y[], double *dfdy, double dfdt[], void *params)
{

    (void)(t);
    std::array<parametres, NB_CLASSE_AGE> *p = reinterpret_cast<std::array<parametres, NB_CLASSE_AGE> *>(params);


    
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, NB_CLASSE_AGE*COMPARTIMENT, NB_CLASSE_AGE*COMPARTIMENT);
    gsl_matrix * m = &dfdy_mat.matrix;

    gsl_matrix_set_zero(m);

    
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {

        double lambda=0;
        for (size_t j = 0; j < NB_CLASSE_AGE; j++){
            lambda = lambda + SOCIAL_CONTACT_MATRIX[classe][j]*y[classe*NB_CLASSE_AGE + I_COMP] /*+ 0.51*data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[A_COMP][jour]*/ ;
        }


        //colonne 0 de la jacobienne
        gsl_matrix_set (m,classe*COMPARTIMENT + S_COMP,classe*COMPARTIMENT + S_COMP,-(*p)[classe].beta[(*p)[classe].i]*lambda); 
        gsl_matrix_set (m,classe*COMPARTIMENT + I_COMP,classe*COMPARTIMENT + S_COMP, (*p)[classe].beta[(*p)[classe].i]*lambda);

        //colonne 1 de la jacobienne
        gsl_matrix_set (m,classe*COMPARTIMENT + S_COMP,classe*COMPARTIMENT + I_COMP,-(*p)[classe].beta[(*p)[classe].i]* y[classe*NB_CLASSE_AGE + S_COMP] * SOCIAL_CONTACT_MATRIX[classe][classe]); 
        gsl_matrix_set (m,classe*COMPARTIMENT + I_COMP,classe*COMPARTIMENT + I_COMP,(*p)[classe].beta[(*p)[classe].i]* y[classe*NB_CLASSE_AGE + S_COMP] * (SOCIAL_CONTACT_MATRIX[classe][classe]) - ( (*p)[classe].delta + (*p)[classe].gamma ));
        gsl_matrix_set (m,classe*COMPARTIMENT + R_COMP,classe*COMPARTIMENT + I_COMP,(*p)[classe].gamma);
        gsl_matrix_set (m,classe*COMPARTIMENT + Q_COMP,classe*COMPARTIMENT + I_COMP,(*p)[classe].delta);

        // colonne 2 de la jacobienne
        // colonne de 0 (aucune dérivation par rapport à R) 

        //colonne 3 de la jacobienne
        gsl_matrix_set (m,classe*COMPARTIMENT + R_COMP,classe*COMPARTIMENT + Q_COMP,(*p)[classe].eps);
        gsl_matrix_set (m,classe*COMPARTIMENT + Q_COMP,classe*COMPARTIMENT + Q_COMP,-((*p)[classe].eps + (*p)[classe].r) );
        gsl_matrix_set (m,classe*COMPARTIMENT + D_COMP,classe*COMPARTIMENT + Q_COMP,(*p)[classe].r);

        // colonne 4 de la jacobienne
        // colonne de 0 (aucune dérivation par rapport à R)

        for (size_t classe2 = 0; classe2 < NB_CLASSE_AGE; classe2++)
        {
            if (classe2 != classe)
            {
                gsl_matrix_set (m,classe2*COMPARTIMENT + S_COMP,classe*COMPARTIMENT + I_COMP,-(*p)[classe2].beta[(*p)[classe2].i]* y[classe2*NB_CLASSE_AGE + S_COMP] * SOCIAL_CONTACT_MATRIX[classe2][classe]); 
                gsl_matrix_set (m,classe2*COMPARTIMENT + I_COMP,classe*COMPARTIMENT + I_COMP,(*p)[classe2].beta[(*p)[classe2].i]* y[classe2*NB_CLASSE_AGE + S_COMP] * (SOCIAL_CONTACT_MATRIX[classe2][classe]) - ( (*p)[classe2].delta + (*p)[classe2].gamma ));
            }
            
        }
        

    }
    
    for (size_t i = 0; i < COMPARTIMENT*NB_CLASSE_AGE; i++)
    {
        dfdt[i] = 0.0; // valeur de la dérivée de l'équation i par rapport à t
    }
    
    
    
    
    return GSL_SUCCESS;
}


/*
        //colonne 0 de la jacobienne
        gsl_matrix_set (m,0,0,-(*p)[classe].beta[(*p)[classe].i]*lambda); 
        gsl_matrix_set (m,1,0, (*p)[classe].beta[(*p)[classe].i]*lambda);

        //colonne 1 de la jacobienne
        gsl_matrix_set (m,0,1,-(*p)[classe].beta[(*p)[classe].i]* y[classe*NB_CLASSE_AGE + S_COMP] * (*p)[classe].social_contact_matrix[classe][classe]); 
        gsl_matrix_set (m,1,1,(*p)[classe].beta[(*p)[classe].i]* y[classe*NB_CLASSE_AGE + S_COMP] * ((*p)[classe].social_contact_matrix[classe][classe]) - ( (*p)[classe].delta + (*p)[classe].gamma ));
        gsl_matrix_set (m,2,1,(*p)[classe].gamma);
        gsl_matrix_set (m,3,1,(*p)[classe].delta);

        // colonne 2 de la jacobienne
        // colonne de 0 (aucune dérivation par rapport à R) 

        //colonne 3 de la jacobienne
        gsl_matrix_set (m,2,3,(*p)[classe].eps);
        gsl_matrix_set (m,3,3,-((*p)[classe].eps + (*p)[classe].r) );
        gsl_matrix_set (m,4,3,(*p)[classe].r);

        // colonne 4 de la jacobienne
        // colonne de 0 (aucune dérivation par rapport à R)
*/





/*
ODE::ODE(int fct_choice=3)
{   
    switch (fct_choice)
    {

    case 1:

        m_function = oscillateur_harm; 
        m_jacobian = jacobian_osc; 

        break;
    case 2:

        m_function = SIRQD; 
        m_jacobian = jacobian_SIRQD; 

        break;

    case 3:
        m_function_discret = SIRQD_discret;

        break;
            
    default:
        break;
    }

}
*/