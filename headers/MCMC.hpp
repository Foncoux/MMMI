#ifndef MCMC_HPP
#define MCMC_HPP



std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> MCMC(std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init,gsl_rng* random_ptr,ODE& f,const Data &data);
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> metropolis(std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init,ODE& f,const Data &data,gsl_rng* r,double &sigma);
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> burning_phase(std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> cond_init,ODE& f,const Data &data,gsl_rng* r,double &sigma);
#endif