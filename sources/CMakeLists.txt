# Crée des variables avec les fichiers à compiler
set(SOURCES
    
    ODE.cpp
    MCMC.cpp
    optimisation_algo.cpp
    fonction_obj.cpp
    fonction_discret.cpp
    read_and_write_data.cpp
    Parametres.cpp
    fonction_continuous.cpp

    )

add_library(sources ${SOURCES})
