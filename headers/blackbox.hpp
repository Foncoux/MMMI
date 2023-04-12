#include "../headers/ODE.hpp"
#include "../headers/functions.hpp"

#include <gsl/gsl_rng.h>

parametres set_parametres(gsl_rng* r,parametres p_opt);

bool validation_parametres(const parametres p);
