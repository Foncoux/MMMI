# Crée des variables avec les fichiers à compiler
set(SOURCES
    
    ODE.cpp
    functions.cpp
    integrator.cpp
    read_data.cpp
    blackbox.cpp
    fonction_obj.cpp
    read_data.cpp
    
    )

add_library(sources ${SOURCES})


