#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <array>

#define COMPARTIMENT 5
#define T_FINAL 289
#define T_DEBUT 0

#define S_COMP 0
#define I_COMP 1
#define R_COMP 2
#define Q_COMP 3
#define D_COMP 4

#define POP_TOT 17282163.0 // 17.282.163

#define DEATH_NB_DAY 289
#define HOSP_NB_DAY 77

#define NB_CONFINEMENT 4

#define DISCRET 1

#define NB_CLASSE_AGE 1

extern std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT;


#endif

