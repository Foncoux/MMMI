include_directories(headers)

link_directories(../lib/googletest) 



file(GLOB TEST *.cpp)
add_executable(test_exe ${TEST} )

set_target_properties(test_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

target_link_libraries(test_exe gtest gtest_main)
target_link_libraries(test_exe config_projet sources GSL::gsl GSL::gslcblas)

add_test(test_integrator test_exe test/test_integrator.cpp)




