#ifndef CONFIG_HPP1
#define CONFIG_HPP1

#include <vector>
#include <string>
#include <time.h>
#include <chrono>

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

extern int COND_INIT_NBR;

extern int STAT_nbr_model_evaluation;
extern int STAT_nbr_model_evaluation_aborted;
extern int STAT_obj_fct_value;

extern  std::chrono::time_point<std::chrono::high_resolution_clock> STAT_time_start;
extern  std::chrono::time_point<std::chrono::high_resolution_clock> STAT_time_end;
extern double STAT_time_taken;

extern struct timespec STAT_CPU_time_start;
extern struct timespec STAT_CPU_time_end;
extern double STAT_CPU_time_taken;

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
        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/1_classe/death_1.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/1_classe/hosp_1.csv"

        #define SOCIAL_CONTACT_MATRIX_filename "../data/DATA_calibration/1_classe/Social_contact_matrix_1.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_1classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_1classe" //4
        #define SAVE_TO_WRITE2 "../data/save_dir/save_SIRQD_1classe_mads" //4
        #define COND_INIT_filename "../data/Conditions_initiales/1_classe_CI.csv"
    #endif

    #if NB_CLASSE_AGE == 2
        #define NB_DATA_DAY_DEATH 3
        #define NB_DATA_DAY_HOSP 3
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 2
        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/2_classe/death_2.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/2_classe/hosp_2.csv"

        #define SOCIAL_CONTACT_MATRIX_filename "../data/DATA_calibration/2_classe/Social_contact_matrix_2.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_2classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_2classe" //4
        #define SAVE_TO_WRITE2 "../data/save_dir/save_SIRQD_2classe_mads" //4
        #define COND_INIT_filename "../data/Conditions_initiales/2_classe_CI.csv"
    #endif

    #if NB_CLASSE_AGE == 4
        #define NB_DATA_DAY_DEATH 5
        #define NB_DATA_DAY_HOSP 5
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 4
        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/4_classe/death_4.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/4_classe/hosp_4.csv"

        #define SOCIAL_CONTACT_MATRIX_filename "../data/DATA_calibration/4_classe/Social_contact_matrix_4.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_4classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_4classe" //4
        #define SAVE_TO_WRITE2 "../data/save_dir/save_SIRQD_4classe_mads" //4
        #define COND_INIT_filename "../data/Conditions_initiales/4_classe_CI.csv"
    #endif


    #if NB_CLASSE_AGE == 8
        #define NB_DATA_DAY_DEATH 9
        #define NB_DATA_DAY_HOSP 9
        #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 8
        #define DAY_DEATH_DATA_filename "../data/DATA_calibration/8_classe/death_8.csv"
        #define DAY_HOSP_DATA_filename "../data/DATA_calibration/8_classe/hosp_8.csv"

        #define SOCIAL_CONTACT_MATRIX_filename "../data/DATA_calibration/8_classe/Social_contact_matrix_8.csv"

        #define SAVE_TO_READ "../data/save_dir/save_SIRQD_8classe" //4
        #define SAVE_TO_WRITE "../data/save_dir/save_SIRQD_8classe" //4
        #define SAVE_TO_WRITE2 "../data/save_dir/save_SIRQD_8classe_mads" //4
        #define COND_INIT_filename "../data/Conditions_initiales/8_classe_CI.csv"
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

