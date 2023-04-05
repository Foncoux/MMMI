include_directories(headers)

find_package(GTest REQUIRED)
file(GLOB TEST *.cpp)
add_executable(test_exe ${TEST})
target_link_libraries(test_exe GTest::GTest GTest::Main)
target_link_libraries(test_exe sources)

add_test(test_1 test_exe test/test_1.cpp)




