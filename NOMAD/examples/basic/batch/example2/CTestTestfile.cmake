# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example2
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/example2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example2BasicBatch "/home/foncoux/Documents/nomad-v.4.3.1/build/release/bin/nomad" "param.txt")
set_tests_properties(Example2BasicBatch PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example2" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example2/CMakeLists.txt;13;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/example2/CMakeLists.txt;0;")
