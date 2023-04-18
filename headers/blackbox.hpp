#ifndef BLACKBOX_HPP
#define BLACKBOX_HPP

#include "../headers/ODE.hpp"
#include "../headers/functions.hpp"

#include <gsl/gsl_rng.h>

parametres blackbox(gsl_rng* random_ptr,ODE &f);

parametres set_parametres_random(gsl_rng* r);
parametres set_parametres_radius(gsl_rng* r,parametres p_opt,double radius);

bool validation_parametres(const parametres p);

#endif