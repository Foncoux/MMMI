
#include <algorithm>
#include <array>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_rng.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
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
            lambda = lambda + (*p)[classe].social_contact_matrix[classe][j]*y[classe*NB_CLASSE_AGE + I_COMP] /*+ 0.51*data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[A_COMP][jour]*/ ;
        }

        f[classe*NB_CLASSE_AGE + S_COMP] = -(*p)[classe].beta[(*p)[classe].i]*lambda*y[classe*NB_CLASSE_AGE + S_COMP];
        f[classe*NB_CLASSE_AGE + I_COMP] = (*p)[classe].beta[(*p)[classe].i]*y[classe*NB_CLASSE_AGE + S_COMP]*y[classe*NB_CLASSE_AGE + I_COMP] - ((*p)[classe].delta+(*p)[classe].gamma)*y[classe*NB_CLASSE_AGE + I_COMP];
        f[classe*NB_CLASSE_AGE + R_COMP] = (*p)[classe].gamma*y[classe*NB_CLASSE_AGE + I_COMP] + (*p)[classe].eps*y[classe*NB_CLASSE_AGE + Q_COMP];
        f[classe*NB_CLASSE_AGE + Q_COMP] = (*p)[classe].delta*y[classe*NB_CLASSE_AGE + I_COMP] - ((*p)[classe].eps + (*p)[classe].r)*y[classe*NB_CLASSE_AGE + Q_COMP];
        f[classe*NB_CLASSE_AGE + D_COMP] = (*p)[classe].r*y[classe*NB_CLASSE_AGE + Q_COMP];
    
        
        return GSL_SUCCESS;
    }
    

}

void integrate(ODE &f,parametres p, double y[])
{
    
    p.i=0;

    gsl_odeiv2_system sys = {f.m_function, f.m_jacobian, COMPARTIMENT, &p};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, 1e-6, 1e-6, 0.0);
    
    

    double t = T_DEBUT;

   

    for (int i = 1; i < T_FINAL; i++)
    {
        if(std::find(TAB_DATE_CONFINEMENT.begin(), TAB_DATE_CONFINEMENT.end(), i) != TAB_DATE_CONFINEMENT.end()){
            p.i++;
        }
        
        double ti = i * (double)T_FINAL / (double)T_FINAL;
        
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        //printf ("%.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4]);

        

        if (status != GSL_SUCCESS)
        {
            printf ("error, return value=%d\n", status);
            break;
        }

        

        f.m_result_integration[0][i] = y[0];
        f.m_result_integration[1][i] = y[1];

//        f.m_result_integration[2][i] = y[2];
//        f.m_result_integration[3][i] = y[3];
//        f.m_result_integration[4][i] = y[4];

       

    }
    
    //std::cout << f.m_result_integration[0][127] << std::endl;
    //printf ("%.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4]);
    //std::cout << f.m_result_integration[1][153] << std::endl;

    gsl_odeiv2_driver_free (d);
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

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {

        double lambda=0;
        for (size_t j = 0; j < NB_CLASSE_AGE; j++){
            lambda = lambda + (*p)[classe].social_contact_matrix[classe][j]*y[classe*NB_CLASSE_AGE + I_COMP] /*+ 0.51*data.social_contact_matrix[classe_age][j]*f[j].m_result_integration[A_COMP][jour]*/ ;
        }

        f[classe*NB_CLASSE_AGE + S_COMP] = -(*p)[classe].beta[(*p)[classe].i]*lambda*y[classe*NB_CLASSE_AGE + S_COMP];
        f[classe*NB_CLASSE_AGE + I_COMP] = (*p)[classe].beta[(*p)[classe].i]*lambda*y[classe*NB_CLASSE_AGE + S_COMP] - ((*p)[classe].delta+(*p)[classe].gamma)*y[classe*NB_CLASSE_AGE + I_COMP];
        f[classe*NB_CLASSE_AGE + R_COMP] = (*p)[classe].gamma*y[classe*NB_CLASSE_AGE + I_COMP] + (*p)[classe].eps*y[classe*NB_CLASSE_AGE + Q_COMP];
        f[classe*NB_CLASSE_AGE + Q_COMP] = (*p)[classe].delta*y[classe*NB_CLASSE_AGE + I_COMP] - ((*p)[classe].eps + (*p)[classe].r)*y[classe*NB_CLASSE_AGE + Q_COMP];
        f[classe*NB_CLASSE_AGE + D_COMP] = (*p)[classe].r*y[classe*NB_CLASSE_AGE + Q_COMP];
    
        
        return GSL_SUCCESS;
    }


    (void)(y);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, NB_CLASSE_AGE, NB_CLASSE_AGE);
    gsl_matrix * m = &dfdy_mat.matrix;
    //première ligne de la jacobienne
    gsl_matrix_set (m, 0, 0, -p->beta[p->i]*y[I_COMP]); //valeur de l'élément (0,0) de la jacobienne
    gsl_matrix_set (m, 0, 1, -p->beta[p->i]*y[S_COMP]); 
    gsl_matrix_set (m, 0, 2, 0.0); 
    gsl_matrix_set (m, 0, 3, 0.0); 
    gsl_matrix_set (m, 0, 4, 0.0); 
    // ligne 2 de la jacobienne 
    gsl_matrix_set (m, 1, 0, p->beta[p->i]*y[I_COMP]); 
    gsl_matrix_set (m, 1, 1, p->beta[p->i]*y[S_COMP] - (p->delta+p->gamma)); 
    gsl_matrix_set (m, 1, 2, 0.0); 
    gsl_matrix_set (m, 1, 3, 0.0); 
    gsl_matrix_set (m, 1, 4, 0.0); 
    //ligne 3 
    gsl_matrix_set (m, 2, 0, 0.0); 
    gsl_matrix_set (m, 2, 1, p->gamma); 
    gsl_matrix_set (m, 2, 2, 0.0); 
    gsl_matrix_set (m, 2, 3, p->eps); 
    gsl_matrix_set (m, 2, 4, 0.0); 
    //ligne 4
    gsl_matrix_set (m, 3, 0, 0.0); 
    gsl_matrix_set (m, 3, 1, p->delta);
    gsl_matrix_set (m, 3, 2, 0.0);
    gsl_matrix_set (m, 3, 3, -p->eps - p->r);
    gsl_matrix_set (m, 3, 4, 0.0);

    gsl_matrix_set (m, 4, 0, 0.0); 
    gsl_matrix_set (m, 4, 1, 0.0); 
    gsl_matrix_set (m, 4, 2, 0.0); 
    gsl_matrix_set (m, 4, 3, p->r); 
    gsl_matrix_set (m, 4, 4, 0.0); 
    

    dfdt[0] = 0.0; // valeur de la dérivée de l'équation 1 par rapport à t
    dfdt[1] = 0.0; // valeur de la dérivée de l'équation 2 par rapport à t
    dfdt[2] = 0.0; // valeur de la dérivée de l'équation 3 par rapport à t
    dfdt[3] = 0.0; // valeur de la dérivée de l'équation 4 par rapport à t
    dfdt[4] = 0.0; // valeur de la dérivée de l'équation 5 par rapport à t
    
    return GSL_SUCCESS;
}



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