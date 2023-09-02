#ifndef FONCTION_CONTINUOUS_HPP
#define FONCTION_CONTINUOUS_HPP


void integrate(ODE &f,parametres p, double y[]);

int oscillateur_harm(double t, const double y[], double f[],void *params);
int jacobian_osc(double t, const double y[], double *dfdy, double dfdt[], void *params);

int model_SIRQD(double t, const double y[], double f[],void *params);

int jacobian_SIRQD(double t, const double y[], double *dfdy, double dfdt[], void *params);



#endif