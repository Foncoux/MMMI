
#include "../headers/fonction_discret.hpp"
#include <iostream>


void SIRQD_discret(std::array<std::array<double, T_FINAL>, COMPARTIMENT> &y,parametres p,int n)
{
    y[S_COMP][n+1] = y[S_COMP][n] - p.beta[p.i]*y[S_COMP][n]*y[I_COMP][n];
    y[I_COMP][n+1] = y[I_COMP][n] + p.beta[p.i]*y[S_COMP][n]*y[I_COMP][n] - (p.delta+p.gamma)*y[I_COMP][n];
    y[R_COMP][n+1] = y[R_COMP][n] + p.gamma*y[I_COMP][n] + p.eps*y[Q_COMP][n];
    y[Q_COMP][n+1] = y[Q_COMP][n] + p.delta*y[I_COMP][n] - (p.eps + p.r)*y[Q_COMP][n];
    y[D_COMP][n+1] = y[D_COMP][n] + p.r*y[Q_COMP][n];
}

void SIRQD_discret_age(std::array<ODE,NB_CLASSE_AGE> &tab_fct,parametres p,int n)
{
    tab_fct[0].m_function_discret(tab_fct[0].m_result_integration,p,n);
}