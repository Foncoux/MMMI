#include "../headers/functions.hpp"
#include "../config/config.hpp"

#include <array>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>


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
    gsl_matrix_set (m, 0, 0, 0.0); //valeur de l'élément (0,0) de la jacobienne
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
int SIRQD(double t, const double y[], double f[],void *params)
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


int jacobian_SIRQD(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    parametres *p = reinterpret_cast<parametres *>(params);

    (void)(t); /* avoid unused parameter warning */
    (void)(params);
    (void)(y);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 5, 5);
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
