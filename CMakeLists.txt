# preciser la version minimale de cmake requise
cmake_minimum_required(VERSION 3.16.3)

enable_testing()
# Nom du projet
project(POO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# compilation en mode debug
set(CMAKE_BUILD_TYPE Debug)

set (Boost_USE_STATIC_LIBS ON)
find_package(GSL REQUIRED)

if (UNIX)
    find_package (Boost)
endif (UNIX)



include_directories(headers)
# On inclut notre bibliothèque dans le processus de CMake
#add_subdirectory(headers)
#add_subdirectory(sources)
#add_subdirectory(test)



# Crée des variables avec les fichiers à compiler
set(MAIN
    main.cpp
    )

# On indique que l'on veut un exécutable "SIRQD" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(main ${MAIN})

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/NOMAD/src)


#find_library(NOMAD_ALGOS_LIB NAMES nomadAlgos PATHS ${CMAKE_CURRENT_SOURCE_DIR}/NOMAD/lib)
#find_library(NOMAD_UTILS_LIB NAMES nomadUtils PATHS ${CMAKE_CURRENT_SOURCE_DIR}/NOMAD/lib)
#find_library(NOMAD_EVAL_LIB NAMES nomadEval PATHS ${CMAKE_CURRENT_SOURCE_DIR}/NOMAD/lib)


#if(OpenMP_CXX_FOUND)
  # target_link_libraries(main PUBLIC libnomadAlgos.so nomadUtils nomadEval sources1 OpenMP::OpenMP_CXX )
#else()
#  target_link_libraries(main PUBLIC ${NOMAD_ALGOS_LIB} ${NOMAD_UTILS_LIB} ${NOMAD_EVAL_LIB} sources1)
#  
#endif()
target_link_libraries(main GSL::gsl GSL::gslcblas)





# Et pour que l'exécutable fonctionne, il faut lui indiquer les bibliothèques dont il dépend
#target_link_libraries(main sources1)

target_compile_options(main PUBLIC -g -Wall -Wextra)


