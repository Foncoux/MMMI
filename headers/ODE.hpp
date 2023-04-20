#ifndef ODE_HPP
#define ODE_HPP

#include <array>
#include <iostream>
#include <fstream>
#include "../headers/functions.hpp"
#include "../config/config.hpp"
#include "../headers/fonction_discret.hpp"

class ODE
{
    private : 
        
        
        
    public :
        int (*m_function)(double, const double [], double [],void*);
        int (*m_jacobian)(double, const double [], double *, double [], void *);
        void (*m_function_discret)(std::array<std::array<double, T_FINAL+1> , COMPARTIMENT> &,parametres,int);

        std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> m_result_integration;

        ODE(int fct_choice);
        void set_condition_initiale(double y[]);
        /*
        void writeData(int taille,int compartiment);
        void evaluate(std::vector<double>& x);
        void resize_result_integration(int taille, int compartiment);
        const std::vector<std::vector<double>>& get_result_integration();
        */
        //void set_result_integration(int taille);
        //int set_compartiment(int fct_choice);
        //void integrate(double a, double b, double h, int taille, std::vector<double> &x0);
        //void writeData(int taille);
        //void multiply_by_nbr(double nbr, std::vector<double> &M);
        
};




#endif
