#ifndef FONCTION_OBJ_HPP
#define FONCTION_OBJ_HPP

double log_likelyhood_death(const Data &data, ODE& output_data);
double fonction_obj(const Data &data, ODE& output_data,int loglikelyhood);
double log_likelyhood_recovered(const Data &data, ODE& output_data);
double log_likelyhood_death_par_day_per_age(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);

double log_likelyhood_hosp_week_day(const Data &data, ODE& output_data);
double fonction_obj_classe_1(const Data &data, ODE& output_data,int loglikelyhood);

double mean_square_recovered(const Data &data, ODE& output_data);

#endif