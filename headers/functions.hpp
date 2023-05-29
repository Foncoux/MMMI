#ifndef FONCTION_HPP
#define FONCTION_HPP

#include <array>
#include "../config/config.hpp"


struct parametres
{   
    std::array<double, NB_CONFINEMENT+1> beta;

    double delta;
    double gamma;
    double eps;
    double r;

    std::array<std::array<double, COMPARTIMENT> , NB_CLASSE_AGE> x0;
    int i;
};



int oscillateur_harm(double t, const double y[], double f[],void *params);
int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params);

int SIRQD(double t, const double y[], double f[],void *params);
int jacobian_SIRQD(double t, const double y[], double *dfdy, double dfdt[], void *params);



#endif