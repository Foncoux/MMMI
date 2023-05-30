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


#endif