
#include <array>
#include <gsl/gsl_sf_log.h>
#include <iostream>

#include "../config/config.hpp"

double min_log_likelyhood_death(std::array<double,DEATH_NB_DAY> observed_data, std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data);
double min_log_likelyhood_hosp(std::array<double,HOSP_NB_DAY> observed_data, std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data);

bool minimisation(double &fct_obj, std::array<double,DEATH_NB_DAY> observed_death, std::array<double,HOSP_NB_DAY> observed_hosp, std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data);
