# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lsh/work12/sorang/host_pc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lsh/work12/sorang/host_pc

# Include any dependencies generated for this target.
include CMakeFiles/lidar_law.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lidar_law.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lidar_law.dir/flags.make

CMakeFiles/lidar_law.dir/lidar/lidar_law.c.o: CMakeFiles/lidar_law.dir/flags.make
CMakeFiles/lidar_law.dir/lidar/lidar_law.c.o: lidar/lidar_law.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/work12/sorang/host_pc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lidar_law.dir/lidar/lidar_law.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lidar_law.dir/lidar/lidar_law.c.o   -c /home/lsh/work12/sorang/host_pc/lidar/lidar_law.c

CMakeFiles/lidar_law.dir/lidar/lidar_law.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lidar_law.dir/lidar/lidar_law.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lsh/work12/sorang/host_pc/lidar/lidar_law.c > CMakeFiles/lidar_law.dir/lidar/lidar_law.c.i

CMakeFiles/lidar_law.dir/lidar/lidar_law.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lidar_law.dir/lidar/lidar_law.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lsh/work12/sorang/host_pc/lidar/lidar_law.c -o CMakeFiles/lidar_law.dir/lidar/lidar_law.c.s

# Object files for target lidar_law
lidar_law_OBJECTS = \
"CMakeFiles/lidar_law.dir/lidar/lidar_law.c.o"

# External object files for target lidar_law
lidar_law_EXTERNAL_OBJECTS =

liblidar_law.a: CMakeFiles/lidar_law.dir/lidar/lidar_law.c.o
liblidar_law.a: CMakeFiles/lidar_law.dir/build.make
liblidar_law.a: CMakeFiles/lidar_law.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/work12/sorang/host_pc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library liblidar_law.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lidar_law.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lidar_law.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lidar_law.dir/build: liblidar_law.a

.PHONY : CMakeFiles/lidar_law.dir/build

CMakeFiles/lidar_law.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lidar_law.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lidar_law.dir/clean

CMakeFiles/lidar_law.dir/depend:
	cd /home/lsh/work12/sorang/host_pc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/work12/sorang/host_pc /home/lsh/work12/sorang/host_pc /home/lsh/work12/sorang/host_pc /home/lsh/work12/sorang/host_pc /home/lsh/work12/sorang/host_pc/CMakeFiles/lidar_law.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lidar_law.dir/depend

