#ifndef FONCTION_OBJ_HPP
#define FONCTION_OBJ_HPP

#include <array>
#include <gsl/gsl_sf_log.h>
#include <iostream>

#include "../config/config.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"


double min_log_likelyhood_death(const Data &data, ODE output_data[]);
double min_log_likelyhood_hosp(const Data &data, ODE output_data[]);
double fonction_obj(const Data &data, ODE output_data[]);

bool minimisation(double &fct_obj,const Data &data, ODE output_data[]);

#endif