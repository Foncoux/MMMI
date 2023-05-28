#include <gsl/gsl_matrix.h>
#include "../config/config.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>


void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_AGE>, NB_CLASSE_AGE>& matrix)
{   
    std::ifstream file("../data/social_contact_matrix.csv");
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    std::string line;
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string value;
        while(std::getline(iss, value, ',')){
            // Traitez ici chaque valeur lue du fichier CSV
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    file.close();    

}

void mult_matrix_vector(const std::array<std::array<double, NB_CLASSE_AGE>, NB_CLASSE_AGE>& matrix, const std::array<double, NB_CLASSE_AGE>& vector, std::array<double, NB_CLASSE_AGE>& result) 
{
    
    for (size_t i = 0; i < NB_CLASSE_AGE; i++){
        result[i] = 0;
        for (size_t j = 0; j < NB_CLASSE_AGE; j++){
            result[i] = result[i] + matrix[i][j] * vector[j];
        }
    }
    
    return;

}


