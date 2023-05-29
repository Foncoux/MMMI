# Crée des variables avec les fichiers à compiler
set(SOURCES
    
    ODE.cpp
    #functions.cpp
    #integration.cpp
    blackbox.cpp
    fonction_obj.cpp
    fonction_discret.cpp
    read_and_write_data.cpp

    )

add_library(sources ${SOURCES})
