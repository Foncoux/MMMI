# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ExampleBasicBatchSingleObjParallel "/home/foncoux/Documents/nomad-v.4.3.1/build/release/bin/nomad" "param.txt")
set_tests_properties(ExampleBasicBatchSingleObjParallel PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel/CMakeLists.txt;15;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel/CMakeLists.txt;0;")
