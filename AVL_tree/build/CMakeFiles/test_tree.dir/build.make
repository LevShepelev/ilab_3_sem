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
CMAKE_SOURCE_DIR = /home/lev/ilab_3_sem/AVL_tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lev/ilab_3_sem/AVL_tree/build

# Include any dependencies generated for this target.
include CMakeFiles/test_tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_tree.dir/flags.make

CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.o: CMakeFiles/test_tree.dir/flags.make
CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.o: ../Google_test/test_tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lev/ilab_3_sem/AVL_tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.o -c /home/lev/ilab_3_sem/AVL_tree/Google_test/test_tree.cpp

CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lev/ilab_3_sem/AVL_tree/Google_test/test_tree.cpp > CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.i

CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lev/ilab_3_sem/AVL_tree/Google_test/test_tree.cpp -o CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.s

# Object files for target test_tree
test_tree_OBJECTS = \
"CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.o"

# External object files for target test_tree
test_tree_EXTERNAL_OBJECTS =

test_tree: CMakeFiles/test_tree.dir/Google_test/test_tree.cpp.o
test_tree: CMakeFiles/test_tree.dir/build.make
test_tree: lib/libgtest.a
test_tree: lib/libgtest_main.a
test_tree: lib/libgtest.a
test_tree: CMakeFiles/test_tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lev/ilab_3_sem/AVL_tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_tree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_tree.dir/build: test_tree

.PHONY : CMakeFiles/test_tree.dir/build

CMakeFiles/test_tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_tree.dir/clean

CMakeFiles/test_tree.dir/depend:
	cd /home/lev/ilab_3_sem/AVL_tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lev/ilab_3_sem/AVL_tree /home/lev/ilab_3_sem/AVL_tree /home/lev/ilab_3_sem/AVL_tree/build /home/lev/ilab_3_sem/AVL_tree/build /home/lev/ilab_3_sem/AVL_tree/build/CMakeFiles/test_tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_tree.dir/depend
