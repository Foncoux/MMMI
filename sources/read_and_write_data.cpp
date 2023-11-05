/**
 * @file read_and_write_data.cpp
 * @author Esteban Foncoux 
 * @brief Lit et écrit dans des fichiers
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iomanip> 
#include <array>
#include <gsl/gsl_rng.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Data.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/read_and_write_data.hpp"


void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX>& matrix,std::string filename)
{   
    
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
    
    std::string line;
    int i=0;
    
    while(std::getline(file, line)){
        int j=0;
        std::istringstream iss(line);
        std::string value;
        while(std::getline(iss, value, ',')){
            matrix[i][j] = std::stod(value);
            //std::cout << matrix[i][j] << "\n\n";
            j++;
        }
        i++;
    }

    file.close();    

}


void write_data(const std::array<ODE, NB_CLASSE_AGE>& f,const std::string& filename1) {
    boost::property_tree::ptree main_tree;

    for (int k = 0; k < NB_CLASSE_AGE; k++) {
        boost::property_tree::ptree ode_tree;

        for (int j = 0; j < COMPARTIMENT_TOT; j++) {
            boost::property_tree::ptree child_tree;
            
            for (int i = 0; i < T_FINAL; i++) {
                boost::property_tree::ptree value;
                value.put_value(f[k].m_result_integration[j][i] * POP_TOT);
                child_tree.push_back(std::make_pair("", value));
            }
            ode_tree.add_child(NAMES_COMPARTIMENT[j], child_tree);
        }

        // Si vous voulez nommer chaque "ODE" dans le JSON (par exemple "ODE1", "ODE2", ...)
        std::string ode_name = "Classe" + std::to_string(k+1);
        main_tree.add_child(ode_name, ode_tree);
    }

    std::string filename = filename1 + ".json";
    std::ofstream myfile(filename);
    if (myfile.is_open()) {
        boost::property_tree::write_json(myfile, main_tree, true);
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }
}


void print_parameter(std::array<parametres,NB_CLASSE_AGE> p)
{
    std::cout << std::endl;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {   
        std::cout << "*** Classe d'age " << classe+1 << " ***" << std::endl;
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
        {
            std::cout << "beta" << i << " : " << p[classe].beta[i] << std::endl;
        }
        
        std::cout << "delta"<< " : " << p[classe].delta << std::endl;
        std::cout << "eps" << " : " << p[classe].eps << std::endl;
        std::cout << "gamma"<< " : " << p[classe].gamma << std::endl;
        std::cout << "r" << " : " << p[classe].r << std::endl;
        
        for (size_t i = 0; i < COMPARTIMENT; i++)
        {
            std::cout << "x0[" << i << "] : " << p[classe].x0[i] << std::endl;
        }
        std::cout << "\n" << std::endl;
    }  
    
}


void write_save_parameters(const std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p, const std::string& save_nbr) {
    boost::property_tree::ptree main_tree;

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++) {
        boost::property_tree::ptree classe_tree;

        boost::property_tree::ptree beta_tree;
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++) {
            beta_tree.put_value(p[NB_PARAM_TOT*classe + PARAM_ID_BETA0 + i]);
            classe_tree.add_child("beta" + std::to_string(i), beta_tree);
            beta_tree.clear();
        }

        classe_tree.put("delta", p[NB_PARAM_TOT*classe + PARAM_ID_DELTA]);
        classe_tree.put("eps", p[NB_PARAM_TOT*classe + PARAM_ID_EPS]);
        classe_tree.put("gamma", p[NB_PARAM_TOT*classe + PARAM_ID_GAMMA]);
        classe_tree.put("r", p[NB_PARAM_TOT*classe + PARAM_ID_R]);
        classe_tree.put("x0", p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect]);

        if(COMPARTIMENT == 6)
        {
            //classe_tree.put("sigma", p[classe].sigma);
        }
        

        main_tree.add_child("classe_" + std::to_string(classe), classe_tree);
    }

    std::string filename = save_nbr + ".json";
    std::ofstream myfile(filename);
    if (myfile.is_open()) {
        boost::property_tree::write_json(myfile, main_tree, true);
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }
}


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_save_parameters(const std::string& save_nbr) {
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;

    std::string filename = save_nbr + ".json";
    boost::property_tree::ptree main_tree;
    boost::property_tree::read_json(filename, main_tree);

    int classe = 0;

    for (const auto& item : main_tree) {
        const auto& classe_tree = item.second;

        for (size_t i = 0; i < NB_CONFINEMENT+1; i++) {
            p[NB_PARAM_TOT*classe + PARAM_ID_BETA0 + i] = classe_tree.get<double>("beta" + std::to_string(i));
        }

        p[NB_PARAM_TOT*classe + PARAM_ID_DELTA] = classe_tree.get<double>("delta");
        p[NB_PARAM_TOT*classe + PARAM_ID_EPS] = classe_tree.get<double>("eps");
        p[NB_PARAM_TOT*classe + PARAM_ID_GAMMA] = classe_tree.get<double>("gamma");
        p[NB_PARAM_TOT*classe + PARAM_ID_R] = classe_tree.get<double>("r");
        p[NB_PARAM_TOT*classe + PARAM_ID_X0_infect] = classe_tree.get<double>("x0");
        if(COMPARTIMENT == 6)
        {
            //p[classe].sigma = classe_tree.get<double>("sigma");
        }

        classe++;
    }

    return p;
}
