#ifndef FONCTION_DISCRET_HPP
#define FONCTION_DISCRET_HPP



int SIRQD_discret(std::array<std::array<double, T_FINAL>, COMPARTIMENT> &y,parametres p,int n,double lambda);
int bb_discret(std::array<ODE,NB_CLASSE_AGE>& f,std::array<parametres,NB_CLASSE_AGE> p,const Data &data);
double force_infection_classe(int jour,int classe_age,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data);

//void SEIRQD_discret(std::array<std::array<double, T_FINAL>, COMPARTIMENT> &y,parametres p,int n,double lambda);
//void SIRQD_discret_age(std::array<ODE,NB_CLASSE_AGE> &tab_fct,parametres p,int n);

#endif