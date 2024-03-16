# preciser la version minimale de cmake requise
cmake_minimum_required(VERSION 3.16.3)

# Nom du projet
project(POO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE=Debug )
# compilation en mode debug


find_package(GSL REQUIRED)

link_directories(${PROJECT_SOURCE_DIR}/../NOMAD_lib/lib)

include_directories(${PROJECT_SOURCE_DIR}/../NOMAD_lib/include/nomad)
include_directories(${PROJECT_SOURCE_DIR}/../NOMAD_lib/include/sgtelib)

include_directories(headers)



# On inclut notre bibliothèque dans le processus de CMake
add_subdirectory(sources)
add_subdirectory(config)



# Crée des variables avec les fichiers à compiler
set(MAIN
    main.cpp
    )



# On indique que l'on veut un exécutable "SIRQD" compilé à partir des fichiers décrits par les variables SRCS et HEADERS




add_executable(main ${MAIN})




#target_compile_options(main PRIVATE -fsanitize=address)
#target_link_options(main PRIVATE -fsanitize=address)
#target_compile_options(main PRIVATE -fsanitize=leak)
#target_link_options(main PRIVATE -fsanitize=leak)
#target_compile_options(main PRIVATE -fsanitize=undefined)
#target_link_options(main PRIVATE -fsanitize=undefined)

target_link_libraries(main PUBLIC sources config_projet GSL::gsl GSL::gslcblas)

if(OpenMP_CXX_FOUND)
  target_link_libraries(main PUBLIC nomadAlgos nomadUtils nomadEval sgtelib OpenMP::OpenMP_CXX)
else()
  target_link_libraries(main PUBLIC nomadAlgos nomadUtils nomadEval sgtelib)
endif()

# Et pour que l'exécutable fonctionne, il faut lui indiquer les bibliothèques dont il dépend
#target_link_libraries(main sources1)

#target_compile_options(main PUBLIC -fsanitize=leak -fsanitize=undefined -fsanitize=address -g -Wall -Wextra -pedantic )
target_compile_options(main PUBLIC -Wall -Wextra -pedantic)


