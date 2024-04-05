#ifndef SETUP_HPP
#define SETUP_HPP

//setup 
#define GIBBS 1
#define METROPOLIS 0

#define ALGO_NOMAD 1
#define ALGO_MCMC 0

#define OPPORTUNISTIC_STRATEGY true
#define NOT_OPPORTUNISTIC_STRATEGY false

#define NB_CONFINEMENT 6
#define DISCRET 1


#define ON_CLUSTER true
#define STOP_FCT_OBJ false

//select wich algorithm is used : 
// ALGO_MCMC or ALGO_NOMAD
#define CHOICE_ALGO_TYPE ALGO_MCMC

 
//select the method used for MCMC :
// GIBBS or METROPOLIS
#define MCMC_PARAM_TYPE_SELECTION GIBBS

//select the strategy used for NOMAD :
// OPPORTUNISTIC_STRATEGY or NOT_OPPORTUNISTIC_STRATEGY
#define NOMAD_STRATEGY OPPORTUNISTIC_STRATEGY


//select the method used for MCMC :
//1 : ORTHO_NP1_QUAD;
//2 : ORTHO_NP1_NEG;
//3 : ORTHO_2N;
#define NOMAD_DIRECTION_TYPE 1

#define NB_CLASSE_AGE NB_CLASSE_AGE_CMAKE




#define SIGMA 0.000003
#define SIGMA_INIT_BURNING 0.0005
#define ALGO 3
#define READ_SAVE_PARAM false
#define WRITE_SAVE_PARAM false

#if NB_CLASSE_AGE_CMAKE == 1
    #define NB_ITER_TOT 16000000
    #define NBR_ITERATION_MADS 32000
#elif NB_CLASSE_AGE_CMAKE == 2
    #define NB_ITER_TOT 40000000
    #define NBR_ITERATION_MADS 80000

#elif NB_CLASSE_AGE_CMAKE == 4
    #define NB_ITER_TOT 60000000
    #define NBR_ITERATION_MADS 120000
#elif NB_CLASSE_AGE_CMAKE == 8
    #define NB_ITER_TOT 100000000
    #define NBR_ITERATION_MADS 200000
#endif

#define BURNIN_STEP NB_ITER_TOT

#define NB_RECORD_IN_STATS_FILE 10000
#define NB_RECORD_IN_STATS_FILE_MADS 200

#define OPTIMISATION true
#define BURNIN_PHASE true
#define MCMC_PHASE false

#endif 