#ifndef BLACKBOX_HPP
#define BLACKBOX_HPP

#include "../headers/ODE.hpp"
#include "../headers/functions.hpp"
#include "../headers/read_and_write_data.hpp"

#include <gsl/gsl_rng.h>

//parametres blackbox(gsl_rng* random_ptr,ODE &f);

parametres set_parametres_random(gsl_rng* r);
parametres set_parametres_radius(gsl_rng* r,parametres p_opt,double radius);

parametres random_search(gsl_rng* random_ptr,ODE f[],const Data &data);
parametres random_search_radius(gsl_rng* random_ptr,ODE f[],const Data &data);
void bb(ODE &f, parametres p, double y[]);
void bb_discret(ODE f[],parametres p);

bool validation_parametres(const parametres p);

#endif