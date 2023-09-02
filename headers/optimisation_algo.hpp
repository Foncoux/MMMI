#ifndef BLACKBOX_HPP
#define BLACKBOX_HPP



std::array<parametres,NB_CLASSE_AGE> random_search(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init);
std::array<parametres,NB_CLASSE_AGE> random_search_radius(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init);
std::array<parametres,NB_CLASSE_AGE> random_search_normal(gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,int fct_obj_choice,std::array<parametres,NB_CLASSE_AGE> cond_init);


bool minimisation(double &fct_obj,const Data &data, std::array<ODE,NB_CLASSE_AGE>& output_data,int fct_obj_choice);




#endif