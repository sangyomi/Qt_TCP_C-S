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
CMAKE_COMMAND = /snap/clion/234/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/234/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sangjun/QT_TCP/QtTCPClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/QtTCPClient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/QtTCPClient.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/QtTCPClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QtTCPClient.dir/flags.make

CMakeFiles/QtTCPClient.dir/main.cpp.o: CMakeFiles/QtTCPClient.dir/flags.make
CMakeFiles/QtTCPClient.dir/main.cpp.o: /home/sangjun/QT_TCP/QtTCPClient/main.cpp
CMakeFiles/QtTCPClient.dir/main.cpp.o: CMakeFiles/QtTCPClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QtTCPClient.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QtTCPClient.dir/main.cpp.o -MF CMakeFiles/QtTCPClient.dir/main.cpp.o.d -o CMakeFiles/QtTCPClient.dir/main.cpp.o -c /home/sangjun/QT_TCP/QtTCPClient/main.cpp

CMakeFiles/QtTCPClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QtTCPClient.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sangjun/QT_TCP/QtTCPClient/main.cpp > CMakeFiles/QtTCPClient.dir/main.cpp.i

CMakeFiles/QtTCPClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QtTCPClient.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sangjun/QT_TCP/QtTCPClient/main.cpp -o CMakeFiles/QtTCPClient.dir/main.cpp.s

# Object files for target QtTCPClient
QtTCPClient_OBJECTS = \
"CMakeFiles/QtTCPClient.dir/main.cpp.o"

# External object files for target QtTCPClient
QtTCPClient_EXTERNAL_OBJECTS =

QtTCPClient: CMakeFiles/QtTCPClient.dir/main.cpp.o
QtTCPClient: CMakeFiles/QtTCPClient.dir/build.make
QtTCPClient: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
QtTCPClient: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.12.8
QtTCPClient: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
QtTCPClient: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
QtTCPClient: CMakeFiles/QtTCPClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable QtTCPClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QtTCPClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QtTCPClient.dir/build: QtTCPClient
.PHONY : CMakeFiles/QtTCPClient.dir/build

CMakeFiles/QtTCPClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QtTCPClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QtTCPClient.dir/clean

CMakeFiles/QtTCPClient.dir/depend:
	cd /home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sangjun/QT_TCP/QtTCPClient /home/sangjun/QT_TCP/QtTCPClient /home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug /home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug /home/sangjun/QT_TCP/QtTCPClient/cmake-build-debug/CMakeFiles/QtTCPClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QtTCPClient.dir/depend

