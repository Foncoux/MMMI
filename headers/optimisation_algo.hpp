#ifndef BLACKBOX_HPP
#define BLACKBOX_HPP



std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> random_search(gsl_rng* random_ptr,ODE& f,const Data &data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init);
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> random_search_radius(gsl_rng* random_ptr,ODE& f,const Data &data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init);
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> random_search_normal(gsl_rng* random_ptr,ODE& f,const Data &data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init);


bool minimisation(double &fct_obj,const Data &data, ODE& output_data,int fct_obj_choice);
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> optimisation_algo_choice(gsl_rng* random_ptr,ODE& f,Data data,int fct_obj_choice,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init);



#endif