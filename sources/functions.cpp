#include "../headers/functions.hpp"



void oscillateur_harm(std::vector<double> &p) {

    double temp = p[1];
    p[1] = -p[0];
    p[0] = temp;

    return;

}