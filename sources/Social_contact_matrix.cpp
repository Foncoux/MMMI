#include <gsl/gsl_matrix.h>
#include "../config/config.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>


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


