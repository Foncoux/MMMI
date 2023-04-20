
#include "../headers/fonction_discret.hpp"
#include <iostream>

void SIRQD_discret(std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> &y,parametres p,int n)
{
    
    y[S_COMP][n+1] = -p.beta[p.i]*y[S_COMP][n]*y[I_COMP][n];
    y[I_COMP][n+1] = p.beta[p.i]*y[S_COMP][n]*y[I_COMP][n] - (p.delta+p.gamma)*y[I_COMP][n];
    y[R_COMP][n+1] = p.gamma*y[I_COMP][n] + p.eps*y[Q_COMP][n];
    y[Q_COMP][n+1] = p.delta*y[I_COMP][n] - (p.eps + p.r)*y[Q_COMP][n];
    y[D_COMP][n+1] = p.r*y[Q_COMP][n];
}