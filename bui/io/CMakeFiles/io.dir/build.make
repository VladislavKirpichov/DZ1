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
CMAKE_BINARY_DIR = /home/DZ1/bui

# Include any dependencies generated for this target.
include io/CMakeFiles/io.dir/depend.make

# Include the progress variables for this target.
include io/CMakeFiles/io.dir/progress.make

# Include the compile flags for this target's objects.
include io/CMakeFiles/io.dir/flags.make

io/CMakeFiles/io.dir/skyscraperio.c.o: io/CMakeFiles/io.dir/flags.make
io/CMakeFiles/io.dir/skyscraperio.c.o: ../io/skyscraperio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/DZ1/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object io/CMakeFiles/io.dir/skyscraperio.c.o"
	cd /home/DZ1/bui/io && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/io.dir/skyscraperio.c.o -c /home/DZ1/io/skyscraperio.c

io/CMakeFiles/io.dir/skyscraperio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/io.dir/skyscraperio.c.i"
	cd /home/DZ1/bui/io && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/DZ1/io/skyscraperio.c > CMakeFiles/io.dir/skyscraperio.c.i

io/CMakeFiles/io.dir/skyscraperio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/io.dir/skyscraperio.c.s"
	cd /home/DZ1/bui/io && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/DZ1/io/skyscraperio.c -o CMakeFiles/io.dir/skyscraperio.c.s

# Object files for target io
io_OBJECTS = \
"CMakeFiles/io.dir/skyscraperio.c.o"

# External object files for target io
io_EXTERNAL_OBJECTS =

io/libio.a: io/CMakeFiles/io.dir/skyscraperio.c.o
io/libio.a: io/CMakeFiles/io.dir/build.make
io/libio.a: io/CMakeFiles/io.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/DZ1/bui/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libio.a"
	cd /home/DZ1/bui/io && $(CMAKE_COMMAND) -P CMakeFiles/io.dir/cmake_clean_target.cmake
	cd /home/DZ1/bui/io && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/io.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
io/CMakeFiles/io.dir/build: io/libio.a

.PHONY : io/CMakeFiles/io.dir/build

io/CMakeFiles/io.dir/clean:
	cd /home/DZ1/bui/io && $(CMAKE_COMMAND) -P CMakeFiles/io.dir/cmake_clean.cmake
.PHONY : io/CMakeFiles/io.dir/clean

io/CMakeFiles/io.dir/depend:
	cd /home/DZ1/bui && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/DZ1 /home/DZ1/io /home/DZ1/bui /home/DZ1/bui/io /home/DZ1/bui/io/CMakeFiles/io.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : io/CMakeFiles/io.dir/depend

