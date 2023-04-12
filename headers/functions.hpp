#ifndef FONCTION_HPP
#define FONCTION_HPP

#include <vector>


struct parametres
{
    double beta;
    double delta;
    double gamma;
    double eps;
    double r;
};



int oscillateur_harm(double t, const double y[], double f[],void *params);
int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params);

int SIRQD(double t, const double y[], double f[],void *params);
int jacobian_SIRQD(double t, const double y[], double *dfdy, double dfdt[], void *params);



#endif