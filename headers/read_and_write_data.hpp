#ifndef READ_WRITE_DATA_HPP
#define READ_WRITE_DATA_HPP

#include <iostream>
#include <fstream>
#include <string>


#include <iomanip> 

#include <array>
#include "../config/config.hpp"

struct Data
{   
    std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_constact_matrix;
    std::array<std::array<double, NB_DAY>, NB_DATA_DAY> day_all;
    std::array<std::array<double, NB_WEEK>, NB_CLASSE_WEEK> week_hosp_ages;
    std::array<std::array<double, NB_MONTH>, NB_CLASSE_MONTH> month_death_ages;
};


void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DAY>& data_day_matrix);
void read_data_week_age(std::string filename,std::array<std::array<double, NB_WEEK>, NB_CLASSE_WEEK>& data_week_matrix);
void read_data_month_age(std::string filename,std::array<std::array<double, NB_MONTH>, NB_CLASSE_MONTH>& data_month_matrix);
void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX>& matrix);

//void read_dataD(std::array<double,DAY> &death);
void read_dataH(std::array<double,NB_DAY> &hosp);
void write_data(std::array<std::array<double, T_FINAL>, COMPARTIMENT> output_data);


#endif