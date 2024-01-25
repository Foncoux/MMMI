#ifndef SETUP_HPP
#define SETUP_HPP


#define SIR 1
#define SIRQD 2
#define SEIRQD 3
#define SEAIRQD 4

#define MCMC_PARAM_TYPE_SELECTION 1
#define TAUX_ACCEPT_OBJ 0.5

#define NB_CONFINEMENT 6
#define DISCRET 1

#define NOMAD_ALGO 0 
#if NOMAD_ALGO == 1 
    #define MODEL_BB 5
#endif
#if NOMAD_ALGO == 0 
    #define MODEL_BB 4 
#endif

#define NB_CLASSE_AGE 2
// 0.0000026083
#define SIGMA 0.000003
//#define SIGMA 0.0000047
#define SIGMA_INIT_BURNING 0.0005
#define ALGO 3
#define READ_SAVE_PARAM true
#define WRITE_SAVE_PARAM true

#define BURNIN_STEP 1000000
#define BURNIN_PHASE true
#define MCMC_PHASE true

#define SETUP SIRQD

#endif 