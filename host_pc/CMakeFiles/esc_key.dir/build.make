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
CMAKE_SOURCE_DIR = /home/lsh/work9/sorang/host_pc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lsh/work9/sorang/host_pc

# Include any dependencies generated for this target.
include CMakeFiles/esc_key.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/esc_key.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/esc_key.dir/flags.make

CMakeFiles/esc_key.dir/teminel_key/esc_key.c.o: CMakeFiles/esc_key.dir/flags.make
CMakeFiles/esc_key.dir/teminel_key/esc_key.c.o: teminel_key/esc_key.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/work9/sorang/host_pc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/esc_key.dir/teminel_key/esc_key.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/esc_key.dir/teminel_key/esc_key.c.o   -c /home/lsh/work9/sorang/host_pc/teminel_key/esc_key.c

CMakeFiles/esc_key.dir/teminel_key/esc_key.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/esc_key.dir/teminel_key/esc_key.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lsh/work9/sorang/host_pc/teminel_key/esc_key.c > CMakeFiles/esc_key.dir/teminel_key/esc_key.c.i

CMakeFiles/esc_key.dir/teminel_key/esc_key.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/esc_key.dir/teminel_key/esc_key.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lsh/work9/sorang/host_pc/teminel_key/esc_key.c -o CMakeFiles/esc_key.dir/teminel_key/esc_key.c.s

# Object files for target esc_key
esc_key_OBJECTS = \
"CMakeFiles/esc_key.dir/teminel_key/esc_key.c.o"

# External object files for target esc_key
esc_key_EXTERNAL_OBJECTS =

libesc_key.a: CMakeFiles/esc_key.dir/teminel_key/esc_key.c.o
libesc_key.a: CMakeFiles/esc_key.dir/build.make
libesc_key.a: CMakeFiles/esc_key.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/work9/sorang/host_pc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libesc_key.a"
	$(CMAKE_COMMAND) -P CMakeFiles/esc_key.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/esc_key.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/esc_key.dir/build: libesc_key.a

.PHONY : CMakeFiles/esc_key.dir/build

CMakeFiles/esc_key.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/esc_key.dir/cmake_clean.cmake
.PHONY : CMakeFiles/esc_key.dir/clean

CMakeFiles/esc_key.dir/depend:
	cd /home/lsh/work9/sorang/host_pc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/work9/sorang/host_pc /home/lsh/work9/sorang/host_pc /home/lsh/work9/sorang/host_pc /home/lsh/work9/sorang/host_pc /home/lsh/work9/sorang/host_pc/CMakeFiles/esc_key.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/esc_key.dir/depend

