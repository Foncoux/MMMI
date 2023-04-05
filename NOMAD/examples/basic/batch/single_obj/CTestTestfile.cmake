# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ExampleSingleObjBasicBatch "/home/foncoux/Documents/nomad-v.4.3.1/build/release/bin/nomad" "param.txt")
set_tests_properties(ExampleSingleObjBasicBatch PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/CMakeLists.txt;14;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj/CMakeLists.txt;0;")
