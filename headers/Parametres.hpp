#ifndef FONCTION_HPP
#define FONCTION_HPP




struct parametres
{   
    std::array<double, NB_CONFINEMENT+1> beta;

    double delta;
    double gamma;
    double eps;
    double r;
    double sigma;

    std::array<double, COMPARTIMENT> x0;
    int i;

    
    
};

std::array<parametres,NB_CLASSE_AGE> set_parametres_random(gsl_rng* r);
std::array<parametres,NB_CLASSE_AGE> set_parametres_radius(gsl_rng* r,std::array<parametres,NB_CLASSE_AGE> p_opt,double radius);
std::array<parametres,NB_CLASSE_AGE> set_parametres_random_normal(gsl_rng* r,double sigma,std::array<parametres,NB_CLASSE_AGE> p_opt);
std::array<parametres,NB_CLASSE_AGE> set_parametres_random_normal_all(gsl_rng* r,double sigma,std::array<parametres,NB_CLASSE_AGE> p_opt);
std::array<parametres,NB_CLASSE_AGE> set_parametres_random_normal_gibbs(gsl_rng* r,double sigma,std::array<parametres,NB_CLASSE_AGE> p_opt);


bool validation_parametres(const std::array<parametres,NB_CLASSE_AGE> p);

void conversion(const std::array<parametres,NB_CLASSE_AGE>& p_struct,std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p_tab);

#endif