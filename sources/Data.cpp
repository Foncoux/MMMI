#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <vector>

#include "../config/config.hpp"
#include "../headers/Data.hpp"

Data::Data()
{
    
    read_data<NB_DATA_DAY, NB_DAY>(DAY_DATA_filename, day_all);
    read_data<NB_DATA_DEATH_AGE_DAY, NB_DAY>(DAY_DEATH_AGE_DATA_filename, day_death_age);
    read_data<NB_CLASSE_MONTH, NB_MONTH>(DEATH_MONTH_AGE_DATA_filename, month_death_ages);

    if (NB_CLASSE_AGE != 1)
    {
        read_data<NB_CLASSE_WEEK, NB_WEEK>(HOSP_WEEK_AGE_DATA_filename, week_hosp_ages); 
    }
    
}


template <std::size_t X, std::size_t Y>
void Data::read_data(std::string filename, std::array<std::array<double, Y>, X>& data_matrix)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        int j = 0;
        std::istringstream iss(line);
        std::string value;
        int skip_first_value = 1;

        while (std::getline(iss, value, ',')) {
            if (skip_first_value == 0) {
                if (std::stod(value) != -1) {
                    data_matrix[i][j] = std::stod(value) / POP_TOT;
                    j++;
                } else {
                    data_matrix[i][j] = -1;
                    j++;
                }
            } else {
                skip_first_value = 0;
            }
        }
        i++;
    }

    file.close();
}