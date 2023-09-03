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


    #define DATA_TO_WRITE "../data/integration"

    #define SAVE_MCMC_WRITE "../data/MCMC_param/save_MCMC"
    #define DATA_MCMC_WRITE "../data/MCMC_result/data_MCMC"

    #define NB_ITE_BLACKBOX 20000
    #define STOP_ALGO 0.0001

    #define BURNIN_STEP 10000
    #define ITE_RECUP_MCMC 10000
    #define NB_POST_DIST 100

    #define RADIUS_INIT 0.05
    
    #define SIGMA 0.7

    #define MODEL 3

#endif


#define CONFIG_OPTION 4

#if CONFIG_OPTION == 1
    #define COMPARTIMENT 6
    #define T_FINAL 295
    #define T_DEBUT 0

    #define S_COMP 0
    #define I_COMP 1
    #define R_COMP 2
    #define Q_COMP 3
    #define D_COMP 4
    #define E_COMP 5

    //#define POP_TOT 17282163.0 // 17.282.163
    #define POP_TOT 17282163.0


    #define POP_classe1 
    #define POP_classe2 
    #define POP_classe3 
    #define POP_classe4 


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

    #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 1

    #define NB_CONFINEMENT 4

    #define DISCRET 1

    #define NB_CLASSE_AGE 1

    #define FCT_OBJ_CHOICE 1

    #define DAY_DATA_filename "../data/day_data.csv"
    #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
    #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age.csv"
    #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
    #define SOCIAL_CONTACT_MATRIX "../data/social_contact_matrix_1.csv"


    extern std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT;
    extern std::array<double, NB_CLASSE_AGE> PROP_PAR_CLASSE;
    extern std::array<std::string, COMPARTIMENT> NAMES_COMPARTIMENT;

    #define ALGO 4
    #define READ_SAVE_PARAM true
    #define WRITE_SAVE_PARAM true
    #define SAVE_TO_READ "../data/save_dir/save_best_save_normal1" //4
    #define SAVE_TO_WRITE "../data/save_dir/save_best_save_normal1" //4
    #define DATA_TO_WRITE "../data/integration"

    #define SAVE_MCMC_WRITE "../data/MCMC_param/save_MCMC"
    #define DATA_MCMC_WRITE "../data/MCMC_result/data_MCMC"

    #define NB_ITE_BLACKBOX 20000
    #define STOP_ALGO 0.00002
    #define BURNIN_STEP 10000
    #define ITE_RECUP_MCMC 10000
    #define NB_POST_DIST 100
    #define RADIUS_INIT 0.05
    #define RADIUS_INIT_BETA 0.5
    #define SIGMA 0.7

    #define MODEL 1

#elif CONFIG_OPTION == 2
    #include <array>

    #define COMPARTIMENT 5
    #define T_FINAL 295
    #define T_DEBUT 0

    #define S_COMP 0
    #define I_COMP 1
    #define R_COMP 2
    #define Q_COMP 3
    #define D_COMP 4

    //#define POP_TOT 17282163.0 // 17.282.163
    #define POP_TOT 17282163.0




    #define POP_classe1 
    #define POP_classe2 
    #define POP_classe3 
    #define POP_classe4 


    #define NB_DAY 295
    #define HOSP_DEBUT 236

    #define NB_DATA_DAY 5
foncoux@foncoux-B550M-S2H:~/Documents/Universite/Master/Master 1-2/MMMI_all/MMMI/build$ 
    #define DEATH_DAY 0
    #define HOSP_DAY 1
    #define PREV_LOW_DAY 2
    #define PREV_MEDIUM_DAY 3
    #define PREV_HIGH_DAY 4

    #define NB_CLASSE_WEEK 4
    #define NB_WEEK 42

    #define NB_CLASSE_MONTH 2
    #define NB_MONTH 10

    #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 4

    #define NB_CONFINEMENT 5

    #define DISCRET 1

    #define NB_CLASSE_AGE 4

    #define FCT_OBJ_CHOICE 1

    #define DAY_DATA_filename "../data/day_data.csv"
    #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age.csv"
    #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
    #define SOCIAL_CONTACT_MATRIX "../data/social_contact_matrix.csv"


    extern std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT;
    extern std::array<double, NB_CLASSE_AGE> PROP_PAR_CLASSE;
    extern std::array<std::string, COMPARTIMENT> NAMES_COMPARTIMENT;

    #define ALGO 1

    #define READ_SAVE_PARAM false
    #define SAVE_TO_READ "2"
    #define SAVE_TO_WRITE "2"

    #define NB_ITE_BLACKBOX 30000
    #define BURNIN_STEP 10000
    #define ITE_RECUP_MCMC 1000
    #define NB_POST_DIST 1000
    #define RADIUS_INIT 0.2
    #define RADIUS_INIT_BETA 0.5
    #define SIGMA 0.025

    #define MODEL 1


#elif CONFIG_OPTION == 3
    #include <array>

    #define COMPARTIMENT 6
    #define T_FINAL 295
    #define T_DEBUT 0

    #define S_COMP 0
    #define I_COMP 1
    #define R_COMP 2
    #define Q_COMP 3
    #define D_COMP 4
    #define E_COMP 5

    //#define POP_TOT 17282163.0 // 17.282.163
    #define POP_TOT 17282163.0


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

    #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 2

    #define NB_CONFINEMENT 4

    #define DISCRET 1

    #define NB_CLASSE_AGE 2

    #define FCT_OBJ_CHOICE 1

    #define DAY_DATA_filename "../data/day_data.csv"
    #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
    #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age2.csv"
    #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
    #define SOCIAL_CONTACT_MATRIX "../data/social_contact_matrix_2.csv"


    extern std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT;
    extern std::array<double, NB_CLASSE_AGE> PROP_PAR_CLASSE;
    extern std::array<std::string, COMPARTIMENT> NAMES_COMPARTIMENT;

    #define ALGO 3

    #define READ_SAVE_PARAM true
    #define WRITE_SAVE_PARAM true
    #define SAVE_TO_READ "../data/save_dir/save_best_save_normal10" //4
    #define SAVE_TO_WRITE "../data/save_dir/save_best_save_normal10" //4
    #define DATA_TO_WRITE "../data/integration"

    #define SAVE_MCMC_WRITE "../data/MCMC_param/save_MCMC"
    #define DATA_MCMC_WRITE "../data/MCMC_result/data_MCMC"

    #define NB_ITE_BLACKBOX 20000
    #define STOP_ALGO 0.00002
    #define BURNIN_STEP 1000
    #define ITE_RECUP_MCMC 1000
    #define NB_POST_DIST 100
    #define RADIUS_INIT 0.1
    #define RADIUS_INIT_BETA 0.5
    #define SIGMA 0.025
    //#define SIGMA 0.1

    #define MODEL 1

#elif CONFIG_OPTION == 5


    #define COMPARTIMENT 2
    #define T_FINAL 295
    #define T_DEBUT 0

    #define S_COMP 0
    #define I_COMP 1
    #define R_COMP 2
    #define Q_COMP 3
    #define D_COMP 4
    #define E_COMP 5

    //#define POP_TOT 17282163.0 // 17.282.163
    #define POP_TOT 17282163.0


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

    #define NB_CLASSE_SOCIAL_CONTACT_MATRIX 1

    #define NB_CONFINEMENT 4

    #define DISCRET 1

    #define NB_CLASSE_AGE 1

    #define FCT_OBJ_CHOICE 1

    #define DAY_DATA_filename "../data/day_data.csv"
    #define DAY_DEATH_AGE_DATA_filename "../data/death_day_age.csv"
    #define HOSP_WEEK_AGE_DATA_filename "../data/hosp_week_age.csv"
    #define DEATH_MONTH_AGE_DATA_filename "../data/death_month_age.csv"
    #define SOCIAL_CONTACT_MATRIX "../data/social_contact_matrix_1.csv"


    extern std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT;
    extern std::array<double, NB_CLASSE_AGE> PROP_PAR_CLASSE;
    extern std::array<std::string, COMPARTIMENT> NAMES_COMPARTIMENT;

    #define ALGO 4
    #define READ_SAVE_PARAM true
    #define WRITE_SAVE_PARAM true
    #define SAVE_TO_READ "../data/save_dir/save_best_save_normal1" //4
    #define SAVE_TO_WRITE "../data/save_dir/save_best_save_normal1" //4
    #define DATA_TO_WRITE "../data/integration"

    #define SAVE_MCMC_WRITE "../data/MCMC_param/save_MCMC"
    #define DATA_MCMC_WRITE "../data/MCMC_result/data_MCMC"

    #define NB_ITE_BLACKBOX 20000
    #define STOP_ALGO 0.00002
    #define BURNIN_STEP 10000
    #define ITE_RECUP_MCMC 10000
    #define NB_POST_DIST 100
    #define RADIUS_INIT 0.05
    #define RADIUS_INIT_BETA 0.5
    #define SIGMA 0.7

    #define MODEL 2

#endif



#endif

