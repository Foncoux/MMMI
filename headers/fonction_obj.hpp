#ifndef FONCTION_OBJ_HPP
#define FONCTION_OBJ_HPP

double log_likelyhood_death(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_hosp(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_infect(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double fonction_obj(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data,int loglikelyhood);
double log_likelyhood_recovered(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_hosp_week(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_death_month(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_death_month2(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_recovered_ages(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_recovered_ages2(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double log_likelyhood_death_par_day_per_age(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);


double min_square_recovered(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double min_square_infect(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double min_square_hosp(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);
double min_square_death(const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data);

#endif