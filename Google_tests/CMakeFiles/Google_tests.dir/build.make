# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/DZ1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/DZ1

# Include any dependencies generated for this target.
include Google_tests/CMakeFiles/Google_tests.dir/depend.make

# Include the progress variables for this target.
include Google_tests/CMakeFiles/Google_tests.dir/progress.make

# Include the compile flags for this target's objects.
include Google_tests/CMakeFiles/Google_tests.dir/flags.make

Google_tests/CMakeFiles/Google_tests.dir/test.cpp.o: Google_tests/CMakeFiles/Google_tests.dir/flags.make
Google_tests/CMakeFiles/Google_tests.dir/test.cpp.o: Google_tests/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/DZ1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Google_tests/CMakeFiles/Google_tests.dir/test.cpp.o"
	cd /home/DZ1/Google_tests && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Google_tests.dir/test.cpp.o -c /home/DZ1/Google_tests/test.cpp

Google_tests/CMakeFiles/Google_tests.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Google_tests.dir/test.cpp.i"
	cd /home/DZ1/Google_tests && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/DZ1/Google_tests/test.cpp > CMakeFiles/Google_tests.dir/test.cpp.i

Google_tests/CMakeFiles/Google_tests.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Google_tests.dir/test.cpp.s"
	cd /home/DZ1/Google_tests && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/DZ1/Google_tests/test.cpp -o CMakeFiles/Google_tests.dir/test.cpp.s

# Object files for target Google_tests
Google_tests_OBJECTS = \
"CMakeFiles/Google_tests.dir/test.cpp.o"

# External object files for target Google_tests
Google_tests_EXTERNAL_OBJECTS =

Google_tests/Google_tests: Google_tests/CMakeFiles/Google_tests.dir/test.cpp.o
Google_tests/Google_tests: Google_tests/CMakeFiles/Google_tests.dir/build.make
Google_tests/Google_tests: io/libio.a
Google_tests/Google_tests: /usr/lib/x86_64-linux-gnu/libgtest_main.a
Google_tests/Google_tests: /usr/lib/x86_64-linux-gnu/libgtest.a
Google_tests/Google_tests: Google_tests/CMakeFiles/Google_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/DZ1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Google_tests"
	cd /home/DZ1/Google_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Google_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Google_tests/CMakeFiles/Google_tests.dir/build: Google_tests/Google_tests

.PHONY : Google_tests/CMakeFiles/Google_tests.dir/build

Google_tests/CMakeFiles/Google_tests.dir/clean:
	cd /home/DZ1/Google_tests && $(CMAKE_COMMAND) -P CMakeFiles/Google_tests.dir/cmake_clean.cmake
.PHONY : Google_tests/CMakeFiles/Google_tests.dir/clean

Google_tests/CMakeFiles/Google_tests.dir/depend:
	cd /home/DZ1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/DZ1 /home/DZ1/Google_tests /home/DZ1 /home/DZ1/Google_tests /home/DZ1/Google_tests/CMakeFiles/Google_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Google_tests/CMakeFiles/Google_tests.dir/depend

