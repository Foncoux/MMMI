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


void write_data_csv(const ODE& f,const std::string& filename1) {
    std::ofstream file(filename1 + ".csv");
    if (file.is_open()) {

        //put headers in the top of the csv file
        for (int i=0;i<COMPARTIMENT_TOT*NB_CLASSE_AGE; i++) {
            file << NAMES_COMPARTIMENT_CSV[i];
            if(i != COMPARTIMENT_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        file << "\n";

        for (size_t day = 0; day < NB_DAY; day++)
        {
            for (int classe=0; classe < NB_CLASSE_AGE; classe++) 
            {
                for (int comp=0;comp<COMPARTIMENT_TOT; comp++) 
                {
                    file << f.m_result_simulation[classe][comp][day];

                    if(comp != COMPARTIMENT_TOT-1)
                    {
                        file << ',';
                    }
                    if(classe != NB_CLASSE_AGE-1 && comp == COMPARTIMENT_TOT-1)
                    {
                        file << ',';
                    }
                }
            }
            file << '\n';
        }
        file.close();
        
    }else{
        std::cerr << "Impossible d'ouvrir le fichier " << filename1 << std::endl;
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

void write_save_parameters_MCMC(const std::vector<std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>> p_storage) {
    
    std::ofstream file(std::string(SAVE_MCMC_WRITE) + ".csv");
    file << std::fixed << std::setprecision(15);
    
    if (file.is_open()){
        //put headers in the top of the csv file
        for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++) {
            file << NAMES_PARAM[i];
            if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        file << "\n";

        //data storage
        for (size_t vec = 0; vec < p_storage.size(); vec++)
        {
            for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++){
                file << p_storage[vec][i];
                if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
                {
                    file << ',';
                }
            }
            file << "\n";
        }
        
        file.close();
        
    } else {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }
}



void write_save_parameters(const std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p, const std::string& save_nbr) {
    std::ofstream file(save_nbr + ".csv");
    file << std::fixed << std::setprecision(15);
    if (file.is_open()) {
        for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++) {
            file << NAMES_PARAM[i];
            if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        file << "\n";

        for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++){
            file << p[i];
            if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        
        file.close();
        
    } else {
        std::cerr << "Impossible d'ouvrir le fichier " << save_nbr << std::endl;
    }
}


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_save_parameters(const std::string& save_nbr)
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    std::ifstream file(save_nbr + ".csv");
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier. (read_save_parameters)" << std::endl;
        exit(0);
    }

    std::string line;
    std::getline(file,line);

    std::getline(file, line);
    std::istringstream iss(line);
    std::string value;
    int i = 0;

    while (std::getline(iss, value, ',') && i < NB_PARAM_TOT*NB_CLASSE_AGE ) {
        p[i] = std::stod(value);
        
        i++;
    }
        
    
    
    file.close();
    return p;
}

