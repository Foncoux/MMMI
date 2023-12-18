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

    std::array<std::array<double, NB_DAY_CALIBRATION>, NB_DATA_DAY> day_all;
    std::array<std::array<double, NB_DAY_CALIBRATION>, NB_DATA_DEATH_AGE_DAY> day_death_age;

    std::array<std::array<double, NB_WEEK>, NB_CLASSE_WEEK> week_hosp_ages;
    std::array<std::array<double, NB_MONTH>, NB_CLASSE_MONTH> month_death_ages;

    template <std::size_t X, std::size_t Y>
    void read_data_csv(std::string filename, std::array<std::array<double, Y>, X>& data_matrix);

};

#endif