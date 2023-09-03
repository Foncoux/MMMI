#ifndef FONCTION_CONTINUOUS_HPP
#define FONCTION_CONTINUOUS_HPP


void integrate(std::array<ODE,NB_CLASSE_AGE>& f,std::array<parametres,NB_CLASSE_AGE>  p, double y[]);
void write_result_conversion_ODE_to_vector(std::array<ODE,NB_CLASSE_AGE>& f, double y[],int jour);
void write_result_conversion_vector_to_ODE(std::array<ODE,NB_CLASSE_AGE>& f, double y[],int jour);

int oscillateur_harm(double t, const double y[], double f[],void *params);
int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params);

int model_SIRQD(double t, const double y[], double f[],void *params);

int jacobian_SIRQD(double t, const double y[], double *dfdy, double dfdt[], void *params);





#endif