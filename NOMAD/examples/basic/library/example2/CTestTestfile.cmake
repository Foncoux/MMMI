# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example2
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example2BasicLib "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/runExampleTest.sh" "./example2_lib.exe")
set_tests_properties(Example2BasicLib PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example2" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example2/CMakeLists.txt;29;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example2/CMakeLists.txt;0;")
