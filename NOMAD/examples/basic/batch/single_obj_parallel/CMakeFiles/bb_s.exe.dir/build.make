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
include examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/progress.make

# Include the compile flags for this target's objects.
include examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/flags.make

examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.o: examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/flags.make
examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.o: ../../examples/basic/batch/single_obj_parallel/bb.cpp
examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.o: examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foncoux/Documents/nomad-v.4.3.1/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.o"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.o -MF CMakeFiles/bb_s.exe.dir/bb.cpp.o.d -o CMakeFiles/bb_s.exe.dir/bb.cpp.o -c /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel/bb.cpp

examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bb_s.exe.dir/bb.cpp.i"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel/bb.cpp > CMakeFiles/bb_s.exe.dir/bb.cpp.i

examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bb_s.exe.dir/bb.cpp.s"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel/bb.cpp -o CMakeFiles/bb_s.exe.dir/bb.cpp.s

# Object files for target bb_s.exe
bb_s_exe_OBJECTS = \
"CMakeFiles/bb_s.exe.dir/bb.cpp.o"

# External object files for target bb_s.exe
bb_s_exe_EXTERNAL_OBJECTS =

examples/basic/batch/single_obj_parallel/bb_s.exe: examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/bb.cpp.o
examples/basic/batch/single_obj_parallel/bb_s.exe: examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/build.make
examples/basic/batch/single_obj_parallel/bb_s.exe: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
examples/basic/batch/single_obj_parallel/bb_s.exe: /usr/lib/x86_64-linux-gnu/libpthread.a
examples/basic/batch/single_obj_parallel/bb_s.exe: examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/foncoux/Documents/nomad-v.4.3.1/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bb_s.exe"
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bb_s.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/build: examples/basic/batch/single_obj_parallel/bb_s.exe
.PHONY : examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/build

examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/clean:
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel && $(CMAKE_COMMAND) -P CMakeFiles/bb_s.exe.dir/cmake_clean.cmake
.PHONY : examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/clean

examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/depend:
	cd /home/foncoux/Documents/nomad-v.4.3.1/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/foncoux/Documents/nomad-v.4.3.1 /home/foncoux/Documents/nomad-v.4.3.1/examples/basic/batch/single_obj_parallel /home/foncoux/Documents/nomad-v.4.3.1/build/release /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel /home/foncoux/Documents/nomad-v.4.3.1/build/release/examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/basic/batch/single_obj_parallel/CMakeFiles/bb_s.exe.dir/depend

