#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <array>

#define COMPARTIMENT 5
#define T_FINAL 295
#define T_DEBUT 0

#define S_COMP 0
#define I_COMP 1
#define R_COMP 2
#define Q_COMP 3
#define D_COMP 4

#define POP_TOT 17282163.0 // 17.282.163

#define NB_DAY 295
#define HOSP_DEBUT 237

#define NB_DATA_DAY 5
#define DEATH_DAY 0
#define HOSP_DAY 1
#define PREV_LOW_DAY 2
#define PREV_MEDIUM_DAY 3
#define PREV_HIGH_DAY 4

#define NB_CLASSE_WEEK 4
#define NB_WEEK 45

#define NB_CLASSE_MONTH 2
#define NB_MONTH 10

#define NB_CLASSE_SOCIAL_CONTACT_MATRIX 4

#define NB_CONFINEMENT 4

#define DISCRET 1

#define NB_CLASSE_AGE 1


extern std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT;


#endif

