#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <vector>
#include "../headers/ODE.hpp"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>


#include <iostream>

void integrate(ODE &f,parametres p, double y[]);

#endif
