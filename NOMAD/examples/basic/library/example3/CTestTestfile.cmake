# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example3
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example3
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example3BasicLib "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/runExampleTest.sh" "./example3_lib.exe")
set_tests_properties(Example3BasicLib PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example3" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example3/CMakeLists.txt;30;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example3/CMakeLists.txt;0;")
