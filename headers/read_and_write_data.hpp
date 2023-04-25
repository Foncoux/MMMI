#ifndef READ_WRITE_DATA_HPP
#define READ_WRITE_DATA_HPP

#include <iostream>
#include <fstream>
#include <string>


#include <iomanip> 

#include <array>
#include "../config/config.hpp"


void read_dataD(std::array<double,DEATH_NB_DAY> &death);
void read_dataH(std::array<double,HOSP_NB_DAY> &hosp);
void write_data(std::array<std::array<double, T_FINAL>, COMPARTIMENT> output_data);


#endif