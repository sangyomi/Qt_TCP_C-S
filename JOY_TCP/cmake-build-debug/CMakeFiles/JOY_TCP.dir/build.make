# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/clion/233/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/233/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sangjun/CLionProjects/JOY_TCP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/JOY_TCP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/JOY_TCP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/JOY_TCP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/JOY_TCP.dir/flags.make

CMakeFiles/JOY_TCP.dir/main.cpp.o: CMakeFiles/JOY_TCP.dir/flags.make
CMakeFiles/JOY_TCP.dir/main.cpp.o: /home/sangjun/CLionProjects/JOY_TCP/main.cpp
CMakeFiles/JOY_TCP.dir/main.cpp.o: CMakeFiles/JOY_TCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/JOY_TCP.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/JOY_TCP.dir/main.cpp.o -MF CMakeFiles/JOY_TCP.dir/main.cpp.o.d -o CMakeFiles/JOY_TCP.dir/main.cpp.o -c /home/sangjun/CLionProjects/JOY_TCP/main.cpp

CMakeFiles/JOY_TCP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JOY_TCP.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sangjun/CLionProjects/JOY_TCP/main.cpp > CMakeFiles/JOY_TCP.dir/main.cpp.i

CMakeFiles/JOY_TCP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JOY_TCP.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sangjun/CLionProjects/JOY_TCP/main.cpp -o CMakeFiles/JOY_TCP.dir/main.cpp.s

# Object files for target JOY_TCP
JOY_TCP_OBJECTS = \
"CMakeFiles/JOY_TCP.dir/main.cpp.o"

# External object files for target JOY_TCP
JOY_TCP_EXTERNAL_OBJECTS =

JOY_TCP: CMakeFiles/JOY_TCP.dir/main.cpp.o
JOY_TCP: CMakeFiles/JOY_TCP.dir/build.make
JOY_TCP: CMakeFiles/JOY_TCP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable JOY_TCP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JOY_TCP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/JOY_TCP.dir/build: JOY_TCP
.PHONY : CMakeFiles/JOY_TCP.dir/build

CMakeFiles/JOY_TCP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/JOY_TCP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/JOY_TCP.dir/clean

CMakeFiles/JOY_TCP.dir/depend:
	cd /home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sangjun/CLionProjects/JOY_TCP /home/sangjun/CLionProjects/JOY_TCP /home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug /home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug /home/sangjun/CLionProjects/JOY_TCP/cmake-build-debug/CMakeFiles/JOY_TCP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/JOY_TCP.dir/depend
