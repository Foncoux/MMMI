# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/foncoux/Documents/nomad-v.4.3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/foncoux/Documents/nomad-v.4.3.1/build/release

# Include any dependencies generated for this target.
include examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/progress.make

# Include the compile flags for this target's objects.
include examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/flags.make

examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o: examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/flags.make
examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o: ../../examples/basic/library/example4/example4_lib.cpp
examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o: examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foncoux/Documents/nomad-v.4.3.1/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o -MF CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o.d -o CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o -c /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4/example4_lib.cpp

examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.i"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4/example4_lib.cpp > CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.i

examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.s"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4/example4_lib.cpp -o CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.s

# Object files for target example4_lib.exe
example4_lib_exe_OBJECTS = \
"CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o"

# External object files for target example4_lib.exe
example4_lib_exe_EXTERNAL_OBJECTS =

examples/basic/library/example4/example4_lib.exe: examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/example4_lib.cpp.o
examples/basic/library/example4/example4_lib.exe: examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/build.make
examples/basic/library/example4/example4_lib.exe: src/libnomadAlgos.so.4.3.1
examples/basic/library/example4/example4_lib.exe: src/libnomadEval.so.4.3.1
examples/basic/library/example4/example4_lib.exe: src/libnomadUtils.so.4.3.1
examples/basic/library/example4/example4_lib.exe: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
examples/basic/library/example4/example4_lib.exe: /usr/lib/x86_64-linux-gnu/libpthread.a
examples/basic/library/example4/example4_lib.exe: ext/sgtelib/libsgtelib.so.2.0.3
examples/basic/library/example4/example4_lib.exe: examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/foncoux/Documents/nomad-v.4.3.1/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example4_lib.exe"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example4_lib.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/build: examples/basic/library/example4/example4_lib.exe
.PHONY : examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/build

examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/clean:
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4 && $(CMAKE_COMMAND) -P CMakeFiles/example4_lib.exe.dir/cmake_clean.cmake
.PHONY : examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/clean

examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/depend:
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/foncoux/Documents/nomad-v.4.3.1 /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/library/example4 /home/foncoux/Documents/nomad-v.4.3.1/build/release /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4 /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/basic/library/example4/CMakeFiles/example4_lib.exe.dir/depend

