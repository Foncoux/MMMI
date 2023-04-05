# CMake generated Testfile for 
# Source directory: /home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve
# Build directory: /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/advanced/library/exampleSuggestAndObserve
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ExampleAdvancedSuggestAndObserve "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/runExampleTest.sh" "./suggestAndObserve.exe")
set_tests_properties(ExampleAdvancedSuggestAndObserve PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve/CMakeLists.txt;41;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve/CMakeLists.txt;0;")
add_test(ExampleAdvancedLoopSuggestAndObserve "/home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/runExampleTest.sh" "./loopSuggestAndObserve.exe")
set_tests_properties(ExampleAdvancedLoopSuggestAndObserve PROPERTIES  WORKING_DIRECTORY "/home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve" _BACKTRACE_TRIPLES "/home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve/CMakeLists.txt;44;add_test;/home/foncoux/Documents/nomad-v.4.3.1/examples/advanced/library/exampleSuggestAndObserve/CMakeLists.txt;0;")
