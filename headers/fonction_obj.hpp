#ifndef FONCTION_OBJ_HPP
#define FONCTION_OBJ_HPP

#include <array>
#include <gsl/gsl_sf_log.h>
#include <iostream>

#include "../config/config.hpp"
#include "../headers/ODE.hpp"
void set_condition_initiale(double y[],std::array<std::array<std::array<double, T_FINAL>, COMPARTIMENT>, NB_CLASSE_AGE> &model_result); /////////////////////////////////////////////

double min_log_likelyhood_death(std::array<double,DEATH_NB_DAY> observed_data, ODE output_data[]);
double min_log_likelyhood_hosp(std::array<double,HOSP_NB_DAY> observed_data, ODE output_data[]);
double fonction_obj(std::array<double,DEATH_NB_DAY> observed_death, std::array<double,HOSP_NB_DAY> observed_hosp, ODE output_data[]);

bool minimisation(double &fct_obj, std::array<double,DEATH_NB_DAY> observed_death, std::array<double,HOSP_NB_DAY> observed_hosp, ODE output_data[]);

#endif