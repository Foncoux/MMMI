#ifndef DATA_HPP
#define DATA_HPP


class Data
{   
    public:

    Data();

    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix;
    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix_home;
    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix_school;
    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix_work;
    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix_transport;
    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix_leisure;
    //std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX> social_contact_matrix_other;

    std::array<std::array<double, NB_DAY_CALIBRATION>, NB_DATA_DAY_DEATH> day_death;
    std::array<std::array<double, NB_DAY_CALIBRATION>, NB_DATA_DAY_DEATH> day_hosp;

    template <std::size_t X, std::size_t Y>
    void read_data_csv(std::string filename, std::array<std::array<double, Y>, X>& data_matrix);

};


extern Data DATA;

void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DEATH_AGE_DAY>& data_day_matrix);

void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DAY>& data_day_matrix);
void read_data_week_age(std::string filename,std::array<std::array<double, NB_WEEK>, NB_CLASSE_WEEK>& data_week_matrix);
void read_data_month_age(std::string filename,std::array<std::array<double, NB_MONTH>, NB_CLASSE_MONTH>& data_month_matrix);
void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX>& matrix,std::string filename);

//void read_dataD(std::array<double,DAY> &death);
void read_dataH(std::array<double,NB_DAY> &hosp);
void write_data(const ODE& f,const std::string& filename);
void write_data_csv(const ODE& f,const std::string& filename);

std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_save_parameters(const std::string& save_nbr);
void write_save_parameters(const std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p, const std::string& save_nbr);

void write_save_parameters_MCMC(const std::vector<std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>> p_storage);

std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_nomad_best_feasible_solution();


#endif