#include "../config/config.hpp"
#include "../headers/functions.hpp"
#include "../headers/ODE.hpp"
#include <array>

void SIRQD_discret(std::array<std::array<double, T_FINAL>, COMPARTIMENT> &y,parametres p,int n);
