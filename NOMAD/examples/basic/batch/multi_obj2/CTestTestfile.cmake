# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/multi_obj2
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/multi_obj2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ExampleMultiObj2BasicBatch "/home/foncoux/Documents/nomad-v.4.3.1/build/release/bin/nomad" "param.txt")
set_tests_properties(ExampleMultiObj2BasicBatch PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/multi_obj2" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/multi_obj2/CMakeLists.txt;14;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/multi_obj2/CMakeLists.txt;0;")
