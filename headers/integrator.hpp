#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <vector>
#include "../headers/ODE.hpp"
#include <iostream>
void RK4(ODE &f, double a, double b, double h,  int taille, std::vector<double> &x0,int compartiment);
void multiply_by_nbr(double nbr, std::vector<double> &M,int compartiment);

#endif
