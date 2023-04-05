# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(example4BasicLib "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/runExampleTest.sh" "./example4_lib.exe")
set_tests_properties(example4BasicLib PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4/CMakeLists.txt;30;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4/CMakeLists.txt;0;")
