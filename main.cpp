
/*
#include <vector>
#include "headers/integrator.hpp"
#include "headers/functions.hpp"
#include "headers/ODE.hpp"

#include <boost/numeric/odeint.hpp>
namespace odeint = boost::numeric::odeint;


#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
*/


/*
int main()
{   
    std::vector<double> x0 {1,0};

    ODE f(1);
    int taille = 20/0.01;
    double a=0; double b=20; double h = 0.01;
    int compartiment =2;
    
    odeint::integrate_adaptive( odeint::make_controlled< error_stepper_type >( 1.0e-10 , 1.0e-6 ) ,
                    harmonic_oscillator , x , 0.0 , 10.0 , 0.01 );



    //RK4(f,a,b,h,taille,x0,compartiment);
    //f.writeData(taille,compartiment);


}
*/

/*
using namespace std;
using namespace boost::numeric::odeint;

// Defining a shorthand for the type of the mathematical state
typedef std::vector< double > state_type;

void oscillateur_harm( const state_type &x , state_type &dxdt , const double t ) {

    dxdt[1] = -x[0];
    dxdt[0] = x[1];

    return;

}

// System to be solved: dx/dt = -2 x
void my_system( const state_type &x , state_type &dxdt , const double t )
{
    dxdt[0] =  0*x[0]  +   1*x[1];
    dxdt[1] = -1*x[0]  - 2.2*x[1];
}

// Observer, prints time and state when called (during integration)
void my_observer( const state_type &x, const double t )
{
    std::cout  << t << "   " << x[0] << "   " << x[1] << std::endl;
}

// ------  Main
int main()
{
    state_type x0(2); // Initial condition, vector of 2 elements (position and velocity)
    x0[0] = 0.0;
    x0[1] = 1.0;

    // Integration parameters
    double t0 = 0.0;
    double t1 = 20.0;
    double dt = 1.0;

    // Define the error stepper
typedef runge_kutta_cash_karp54< state_type > error_stepper_rkck54;

// Error bounds
double err_abs = 1.0e-10;
double err_rel = 1.0e-6;

// Fire! 
integrate_adaptive( make_controlled( err_abs , err_rel , error_stepper_rkck54() ) , 
                    oscillateur_harm , x0 , t0 , t1 , dt , my_observer );

}
*/


#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int oscillateur_harm(double t, const double y[], double f[],void *params)
{
    (void)(t); /* avoid unused parameter warning */
    (void)(params);
    f[0] = y[1];
    f[1] = -y[0];
    return GSL_SUCCESS;

}


int func (double t, const double y[], double f[],void *params)
{
    (void)(t); /* avoid unused parameter warning */
    double mu = *(double *)params;
    f[0] = y[1];
    f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
    return GSL_SUCCESS;
}
int jacobian (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    (void)(t); /* avoid unused parameter warning */
    (void)(params);
    (void)(y);
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix * m = &dfdy_mat.matrix;
    gsl_matrix_set (m, 0, 0, 0.0); //valeur de l'élément (0,0) de la jacobienne
    gsl_matrix_set (m, 0, 1, 1.0);//valeur de l'élément (0,1) de la jacobienne
    gsl_matrix_set (m, 1, 0, - 1.0); //valeur de l'élément (1,0) de la jacobienne
    gsl_matrix_set (m, 1, 1, 0.0); //valeur de l'élément (1,1) de la jacobienne

    dfdt[0] = 0.0; // valeur de la dérivée de l'équation 1 par rapport à t
    dfdt[1] = 0.0; // valeur de la dérivée de l'équation 2 par rapport à t
    return GSL_SUCCESS;
}

int jac (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    (void)(t); /* avoid unused parameter warning */
    double mu = *(double *)params;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix * m = &dfdy_mat.matrix;
    gsl_matrix_set (m, 0, 0, 0.0); //valeur de l'élément (0,0) de la jacobienne
    gsl_matrix_set (m, 0, 1, 1.0);//valeur de l'élément (0,1) de la jacobienne
    gsl_matrix_set (m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0); //valeur de l'élément (1,0) de la jacobienne
    gsl_matrix_set (m, 1, 1, -mu*(y[0]*y[0] - 1.0)); //valeur de l'élément (1,1) de la jacobienne

    dfdt[0] = 0.0; // valeur de la dérivée de l'équation 1 par rapport à t
    dfdt[1] = 0.0; // valeur de la dérivée de l'équation 2 par rapport à t
    return GSL_SUCCESS;
}

int main (void)
{
    
    double mu = 10;
    gsl_odeiv2_system sys = {oscillateur_harm, jacobian, 2, &mu};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45,
    1e-6, 1e-6, 0.0);
    int i;
    double t = 0.0, t1 = 100.0;
    double y[2] = { 1.0, 0.0 };
    for (i = 1; i <= 100; i++)
    {
        double ti = i * t1 / 100.0;
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
    if (status != GSL_SUCCESS)
    {
        printf ("error, return value=%d\n", status);
        break;
    }
    
    }
    gsl_odeiv2_driver_free (d);
    return 0;
}


/*
int main (void)
{
const gsl_odeiv2_step_type * T = gsl_odeiv2_step_rk8pd;
gsl_odeiv2_step * s = gsl_odeiv2_step_alloc (T, 2);
gsl_odeiv2_control * c = gsl_odeiv2_control_y_new (1e-6, 0.0);
gsl_odeiv2_evolve * e = gsl_odeiv2_evolve_alloc (2);
double mu = 10;
gsl_odeiv2_system sys = {func, jac, 2, &mu};
double t = 0.0, t1 = 100.0;
double h = 1e-6;
double y[2] = { 1.0, 0.0 };
while (t < t1)
{
    int status = gsl_odeiv2_evolve_apply (e, c, s,
    &sys,
    &t, t1,
    &h, y);
    if (status != GSL_SUCCESS)
    {
        break;
    }
    printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
}
gsl_odeiv2_evolve_free (e);
gsl_odeiv2_control_free (c);
gsl_odeiv2_step_free (s);
return 0;
}

*/