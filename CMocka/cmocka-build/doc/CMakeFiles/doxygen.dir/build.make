# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-1.1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build

# Utility rule file for doxygen.

# Include the progress variables for this target.
include doc/CMakeFiles/doxygen.dir/progress.make

doc/CMakeFiles/doxygen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Writing documentation to /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build/doc/doc..."
	cd /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-1.1.1/doc && /usr/bin/doxygen /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build/doc/Doxyfile

doxygen: doc/CMakeFiles/doxygen
doxygen: doc/CMakeFiles/doxygen.dir/build.make

.PHONY : doxygen

# Rule to build all files generated by this target.
doc/CMakeFiles/doxygen.dir/build: doxygen

.PHONY : doc/CMakeFiles/doxygen.dir/build

doc/CMakeFiles/doxygen.dir/clean:
	cd /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build/doc && $(CMAKE_COMMAND) -P CMakeFiles/doxygen.dir/cmake_clean.cmake
.PHONY : doc/CMakeFiles/doxygen.dir/clean

doc/CMakeFiles/doxygen.dir/depend:
	cd /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-1.1.1 /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-1.1.1/doc /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build/doc /home/thibaud/Bureau/QwirkleInC/Qwirkle/CMocka/cmocka-build/doc/CMakeFiles/doxygen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/doxygen.dir/depend

