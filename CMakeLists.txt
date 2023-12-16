# preciser la version minimale de cmake requise
cmake_minimum_required(VERSION 3.16.3)


# Nom du projet
project(POO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# compilation en mode debug
set(CMAKE_BUILD_TYPE Debug)

find_package(GSL REQUIRED)

option(BUILD_TESTING "Are we building for testing?" OFF)


#enable_testing()

link_directories(./lib/NOMAD/lib)

include_directories(${CMAKE_SOURCE_DIR}/lib/NOMAD/include)
include_directories(headers)


# On inclut notre bibliothèque dans le processus de CMake
add_subdirectory(sources)
#add_subdirectory(test)
add_subdirectory(config)



# Crée des variables avec les fichiers à compiler
set(MAIN
    main.cpp
    )



# On indique que l'on veut un exécutable "SIRQD" compilé à partir des fichiers décrits par les variables SRCS et HEADERS




add_executable(main ${MAIN})

target_link_libraries(main PUBLIC sources config_projet GSL::gsl GSL::gslcblas)

if(OpenMP_CXX_FOUND)
  target_link_libraries(main PUBLIC nomadAlgos nomadUtils nomadEval OpenMP::OpenMP_CXX)
else()
  target_link_libraries(main PUBLIC nomadAlgos nomadUtils nomadEval)
endif()






# Et pour que l'exécutable fonctionne, il faut lui indiquer les bibliothèques dont il dépend
#target_link_libraries(main sources1)

target_compile_options(main PUBLIC -g -Wall -Wextra -pedantic )


