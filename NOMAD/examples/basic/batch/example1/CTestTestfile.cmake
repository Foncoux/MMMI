# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example1
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/example1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example1BasicBatch "/home/foncoux/Documents/nomad-v.4.3.1/build/release/bin/nomad" "param.txt")
set_tests_properties(Example1BasicBatch PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example1" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example1/CMakeLists.txt;13;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example1/CMakeLists.txt;0;")
