#ifndef CONFIG_HPP1
#define CONFIG_HPP1

#include "setup.hpp"

void config_table_extern();
void set_social_contact_matrix(std::vector<std::vector<double>>& matrix, std::string filename);

#define POP_TOT 17282163.0

#define S_COMP 0
#define I_COMP 1
#define R_COMP 2
#define Q_COMP 3
#define D_COMP 4
#define Q_ENTRY_COMP 5
#define D_ENTRY_COMP 6
#define E_COMP 7
/*295*/
#define NB_DAY 350
#define NB_DAY_CALIBRATION 282
#define HOSP_DEBUT 237

#define NB_DATA_DAY 6
#define NB_DATA_DEATH_AGE_DAY 3
#define DEATH_DAY 0
#define HOSP_DAY 1
#define PREV_LOW_DAY 2
#define PREV_MEDIUM_DAY 3
#define PREV_HIGH_DAY 4
#define HOSP_WEEK_DAY 5

#define NB_CLASSE_WEEK 1
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
    #define PARAM_ID_BETA0 5

    #define NB_PARAM_TOT (NB_PARAM + NB_CONFINEMENT + 1)

    #define PHANTOM_COMPART 2
    #define COMPARTIMENT 5
    #define COMPARTIMENT_TOT (PHANTOM_COMPART+COMPARTIMENT)
    #define FCT_OBJ_CHOICE 1

    extern std::vector<int> TAB_DATE_CONFINEMENT;
    extern std::vector<double> PROP_PAR_CLASSE;
    extern std::vector<std::string> NAMES_COMPARTIMENT;
    extern std::vector<std::string> NAMES_COMPARTIMENT_CSV;

    extern std::vector<std::string> NAMES_PARAM;
    extern std::vector<std::vector<double>> SOCIAL_CONTACT_MATRIX;
    extern std::vector<std::string> SELECT_CLASSE_AGE;
  
    

    #if NB_CLASSE_AGE == 1
        #define NB_DATA_DAY_DEATH 1
        #define NB_DATA_DAY_HOSP 1
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 1
        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/All/day_death_csv.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/All/day_hosp_csv.csv"

        #define DAY_DATA_filename "../data/day_data.csv"
        #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
        #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week.csv"
        #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
        #define SOCIAL_CONTACT_MATRIX_filename "../data/DATA_calibration/All/social_contact_matrix_1.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_1classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_1classe" //4
    #endif

    #if NB_CLASSE_AGE == 2
        #define NB_DATA_DAY_DEATH 3
        #define NB_DATA_DAY_HOSP 3
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 2
        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/0-65_65-inf/day_death_csv_0-65_65-inf.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/0-65_65-inf/day_hosp_csv_0-65_65-inf.csv"

        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/0-65_65-inf/day_death_csv_0-65_65-inf.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/0-65_65-inf/day_hosp_csv_0-65_65-inf.csv"

        #define DAY_DATA_filename "../data/day_data.csv"
        #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
        #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age2.csv"
        #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
        #define SOCIAL_CONTACT_MATRIX_filename "../data/DATA_calibration/0-65_65-inf/social_contact_matrix_0-65_65-inf.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_2classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_2classe" //4
    #endif


    #define DATA_TO_WRITE "../data/integration"

    #define SAVE_MCMC_WRITE "../data/MCMC_param/save_MCMC"
    #define DATA_MCMC_WRITE "../data/MCMC_result/data_MCMC"

    #define NB_ITE_BLACKBOX 20000
    #define STOP_ALGO 0.00001

    #define ITE_RECUP_MCMC 1000
    #define NB_POST_DIST 100

    #define RADIUS_INIT 0.05
    
    

#endif

#endif

