#ifndef BLACKBOX_HPP
#define BLACKBOX_HPP

#include "../headers/ODE.hpp"
#include "../headers/functions.hpp"

#include <gsl/gsl_rng.h>

//parametres blackbox(gsl_rng* random_ptr,ODE &f);

parametres set_parametres_random(gsl_rng* r);
parametres set_parametres_radius(gsl_rng* r,parametres p_opt,double radius);

parametres random_search(gsl_rng* random_ptr,ODE &f,std::array<double,DEATH_NB_DAY> death,std::array<double,HOSP_NB_DAY> hosp);
parametres random_search_radius(gsl_rng* random_ptr,ODE f[],std::array<double,DEATH_NB_DAY> death,std::array<double,HOSP_NB_DAY> hosp,    std::array<std::array<std::array<double, T_FINAL>, COMPARTIMENT>, NB_CLASSE_AGE>& model_result);
void bb(ODE &f, parametres p, double y[]);
void bb_discret(ODE f[],parametres p);

bool validation_parametres(const parametres p);

#endif