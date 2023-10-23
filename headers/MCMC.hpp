#ifndef MCMC_HPP
#define MCMC_HPP



std::array<parametres,NB_CLASSE_AGE> MCMC(std::array<parametres,NB_CLASSE_AGE> cond_init,gsl_rng* random_ptr,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data);
std::array<parametres,NB_CLASSE_AGE> metropolis(std::array<parametres,NB_CLASSE_AGE> cond_init,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,gsl_rng* r);
std::array<parametres,NB_CLASSE_AGE> burning_phase(std::array<parametres,NB_CLASSE_AGE> cond_init,std::array<ODE,NB_CLASSE_AGE>& f,const Data &data,gsl_rng* r);
#endif