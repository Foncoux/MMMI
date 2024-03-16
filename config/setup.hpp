#ifndef SETUP_HPP
#define SETUP_HPP

#define ON_CLUSTER true
#define STOP_FCT_OBJ false

#define SIRQD 2


//select the method used for MCMC :
// 0 = metropolis 
// 1 = Gibbs
#define MCMC_PARAM_TYPE_SELECTION 1

#define NB_CONFINEMENT 6
#define DISCRET 1


//select wich algorithm is used : 
// 0 = MCMC
// 1 = NOMAD
#define NOMAD_ALGO 0


#define NB_CLASSE_AGE 1
#define SIGMA 0.000003
#define SIGMA_INIT_BURNING 0.0005
#define ALGO 3
#define READ_SAVE_PARAM false
#define WRITE_SAVE_PARAM false

#define NB_ITER_TOT 30000000
#define BURNIN_STEP NB_ITER_TOT

#define NB_RECORD_IN_STATS_FILE 1000

#define OPTIMISATION true
#define BURNIN_PHASE true
#define MCMC_PHASE false

#define SETUP SIRQD

#endif 