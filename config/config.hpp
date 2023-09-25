#ifndef CONFIG_HPP1
#define CONFIG_HPP1

#include "setup.hpp"

void config_table_extern();
void set_social_contact_matrix(std::vector<std::vector<double>>& matrix, std::string filename);

#define T_FINAL 295
#define T_DEBUT 0

#define POP_TOT 17282163.0

#define S_COMP 0
#define I_COMP 1
#define R_COMP 2
#define Q_COMP 3
#define D_COMP 4
#define E_COMP 5

#define NB_DAY 295
#define HOSP_DEBUT 237

#define NB_DATA_DAY 5
#define NB_DATA_DEATH_AGE_DAY 3
#define DEATH_DAY 0
#define HOSP_DAY 1
#define PREV_LOW_DAY 2
#define PREV_MEDIUM_DAY 3
#define PREV_HIGH_DAY 4

#define NB_CLASSE_WEEK 2
#define NB_WEEK 42

#define NB_CLASSE_MONTH 2
#define NB_MONTH 10


#if SETUP == SIRQD

    #define NB_PARAM 5
    #define PARAM_ID_DELTA 0
    #define PARAM_ID_GAMMA 1
    #define PARAM_ID_EPS 2
    #define PARAM_ID_R 3

    #define PARAM_ID_X0_infect 4

    #define NB_PARAM_TOT NB_PARAM + NB_CONFINEMENT + 1


    #define COMPARTIMENT 5
    #define FCT_OBJ_CHOICE 1

    extern std::vector<int> TAB_DATE_CONFINEMENT;
    extern std::vector<double> PROP_PAR_CLASSE;
    extern std::vector<std::string> NAMES_COMPARTIMENT;
    extern std::vector<std::vector<double>> SOCIAL_CONTACT_MATRIX;

    #if NB_CLASSE_AGE == 1
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 1

        #define DAY_DATA_filename "../data/day_data.csv"
        #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
        #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age.csv"
        #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
        #define SOCIAL_CONTACT_MATRIX_filename "../data/social_contact_matrix_1.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_1classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_1classe" //4
    #endif

    #if NB_CLASSE_AGE == 2
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 2

        #define DAY_DATA_filename "../data/day_data.csv"
        #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
        #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age2.csv"
        #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
        #define SOCIAL_CONTACT_MATRIX_filename "../data/social_contact_matrix_2.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_2classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_2classe" //4
    #endif


    #define DATA_TO_WRITE "../data/integration"

    #define SAVE_MCMC_WRITE "../data/MCMC_param/save_MCMC"
    #define DATA_MCMC_WRITE "../data/MCMC_result/data_MCMC"

    #define NB_ITE_BLACKBOX 20000
    #define STOP_ALGO 0.0001

    #define BURNIN_STEP 10000
    #define ITE_RECUP_MCMC 1000
    #define NB_POST_DIST 100

    #define RADIUS_INIT 0.05
    
    #define SIGMA 0.1

#endif

#endif

