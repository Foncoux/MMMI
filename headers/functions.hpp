#ifndef FONCTION_HPP
#define FONCTION_HPP

#include <vector>


struct parametres
{
    double m;
};



int oscillateur_harm(double t, const double y[], double f[],void *params);
int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params);

#endif