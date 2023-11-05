#ifndef READ_WRITE_DATA_HPP
#define READ_WRITE_DATA_HPP

void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DEATH_AGE_DAY>& data_day_matrix);

void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DAY>& data_day_matrix);
void read_data_week_age(std::string filename,std::array<std::array<double, NB_WEEK>, NB_CLASSE_WEEK>& data_week_matrix);
void read_data_month_age(std::string filename,std::array<std::array<double, NB_MONTH>, NB_CLASSE_MONTH>& data_month_matrix);
void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX>& matrix,std::string filename);

//void read_dataD(std::array<double,DAY> &death);
void read_dataH(std::array<double,NB_DAY> &hosp);
void write_data(const std::array<ODE, NB_CLASSE_AGE>& f,const std::string& filename);

void print_parameter(std::array<parametres,NB_CLASSE_AGE> p);
std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_save_parameters(const std::string& save_nbr);
void write_save_parameters(const std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p, const std::string& save_nbr);



#endif