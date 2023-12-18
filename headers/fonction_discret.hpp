#ifndef FONCTION_DISCRET_HPP
#define FONCTION_DISCRET_HPP


int model(ODE &f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> &param_opti);


double force_infection_classe(int jour,int classe_age,ODE& f);

int bb_discret_new(ODE& f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p);
int SIRQD_discret_new(std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT> &y,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,int n,double lambda, int classe, int confinement);


int model(ODE& f,const NOMAD::EvalPoint &x);
int bb_discret_new(ODE& f,const NOMAD::EvalPoint &p);
int SIRQD_discret_new(std::array<std::array<double, NB_DAY>, COMPARTIMENT_TOT> &y,const NOMAD::EvalPoint &p,int n,double lambda, int classe, int confinement);


#endif