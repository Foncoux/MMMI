#ifndef FONCTION_DISCRET_HPP
#define FONCTION_DISCRET_HPP


int model(std::array<ODE,NB_CLASSE_AGE> &f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> &param_opti,const Data &data);


double force_infection_classe(int jour,int classe_age,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data);

int bb_discret_new(std::array<ODE,NB_CLASSE_AGE>& f,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,const Data &data);
int SIRQD_discret_new(std::array<std::array<double, T_FINAL>, COMPARTIMENT_TOT> &y,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p,int n,double lambda, int classe, int confinement);




#endif