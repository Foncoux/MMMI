# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_MPIparallel
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_MPIparallel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ExampleBasicBatchSingleObjMPIParallel "/home/foncoux/Documents/nomad-v.4.3.1/build/release/bin/nomad" "param.txt")
set_tests_properties(ExampleBasicBatchSingleObjMPIParallel PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_MPIparallel" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_MPIparallel/CMakeLists.txt;23;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_MPIparallel/CMakeLists.txt;0;")
