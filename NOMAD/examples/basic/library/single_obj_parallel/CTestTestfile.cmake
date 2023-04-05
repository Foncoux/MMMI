# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/single_obj_parallel
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/single_obj_parallel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SingleObjParallelBasicLib "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/runExampleTest.sh" "./single_obj_parallel.exe")
set_tests_properties(SingleObjParallelBasicLib PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/single_obj_parallel" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/single_obj_parallel/CMakeLists.txt;29;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/single_obj_parallel/CMakeLists.txt;0;")
