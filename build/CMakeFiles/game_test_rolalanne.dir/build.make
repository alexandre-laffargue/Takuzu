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
CMAKE_SOURCE_DIR = /net/cremi/rolalanne/espaces/travail/takuzu-06b

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /net/cremi/rolalanne/espaces/travail/takuzu-06b/build

# Include any dependencies generated for this target.
include CMakeFiles/game_test_rolalanne.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game_test_rolalanne.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game_test_rolalanne.dir/flags.make

CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.o: CMakeFiles/game_test_rolalanne.dir/flags.make
CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.o: ../game_test_rolalanne.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/net/cremi/rolalanne/espaces/travail/takuzu-06b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.o -c /net/cremi/rolalanne/espaces/travail/takuzu-06b/game_test_rolalanne.c

CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /net/cremi/rolalanne/espaces/travail/takuzu-06b/game_test_rolalanne.c > CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.i

CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /net/cremi/rolalanne/espaces/travail/takuzu-06b/game_test_rolalanne.c -o CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.s

# Object files for target game_test_rolalanne
game_test_rolalanne_OBJECTS = \
"CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.o"

# External object files for target game_test_rolalanne
game_test_rolalanne_EXTERNAL_OBJECTS =

game_test_rolalanne: CMakeFiles/game_test_rolalanne.dir/game_test_rolalanne.c.o
game_test_rolalanne: CMakeFiles/game_test_rolalanne.dir/build.make
game_test_rolalanne: libgame.a
game_test_rolalanne: CMakeFiles/game_test_rolalanne.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/net/cremi/rolalanne/espaces/travail/takuzu-06b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable game_test_rolalanne"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game_test_rolalanne.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game_test_rolalanne.dir/build: game_test_rolalanne

.PHONY : CMakeFiles/game_test_rolalanne.dir/build

CMakeFiles/game_test_rolalanne.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game_test_rolalanne.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game_test_rolalanne.dir/clean

CMakeFiles/game_test_rolalanne.dir/depend:
	cd /net/cremi/rolalanne/espaces/travail/takuzu-06b/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /net/cremi/rolalanne/espaces/travail/takuzu-06b /net/cremi/rolalanne/espaces/travail/takuzu-06b /net/cremi/rolalanne/espaces/travail/takuzu-06b/build /net/cremi/rolalanne/espaces/travail/takuzu-06b/build /net/cremi/rolalanne/espaces/travail/takuzu-06b/build/CMakeFiles/game_test_rolalanne.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game_test_rolalanne.dir/depend

