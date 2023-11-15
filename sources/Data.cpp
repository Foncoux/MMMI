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
    
    //read_data<NB_DATA_DAY, NB_DAY>(DAY_DATA_filename, day_all);
    //read_data<NB_DATA_DEATH_AGE_DAY, NB_DAY>(DAY_DEATH_AGE_DATA_filename, day_death_age);
    //read_data<NB_CLASSE_MONTH, NB_MONTH>(DEATH_MONTH_AGE_DATA_filename, month_death_ages);

    //read_data<NB_CLASSE_WEEK, NB_WEEK>(HOSP_WEEK_AGE_DATA_filename, week_hosp_ages);

    read_data_csv<NB_DATA_DAY_DEATH, NB_DAY>(DAY_DEATH_DATA_filename, day_death);
    read_data_csv<NB_DATA_DAY_HOSP, NB_DAY>(DAY_HOSP_DATA_filename, day_hosp);

    
}


template <std::size_t X, std::size_t Y>
void Data::read_data_csv(std::string filename, std::array<std::array<double, Y>, X>& data_matrix)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    std::string line;
    std::getline(file,line);

    int row = 0;
    while (std::getline(file, line) && row < Y) {
        std::istringstream iss(line);
        std::string value;
        int col = 0;

        while (std::getline(iss, value, ',') && col < X ) {
            if (std::stod(value) != -1) {
                data_matrix[col][row] = std::stod(value);
            } else {
                data_matrix[col][row] = -1;
            }
            col++;
        }
        row++;
    }

    file.close();
}