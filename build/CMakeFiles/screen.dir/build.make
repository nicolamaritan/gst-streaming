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
CMAKE_SOURCE_DIR = /home/nicolamaritan/Repositories/video-streamer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicolamaritan/Repositories/video-streamer/build

# Include any dependencies generated for this target.
include CMakeFiles/screen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/screen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/screen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/screen.dir/flags.make

CMakeFiles/screen.dir/src/screen.c.o: CMakeFiles/screen.dir/flags.make
CMakeFiles/screen.dir/src/screen.c.o: ../src/screen.c
CMakeFiles/screen.dir/src/screen.c.o: CMakeFiles/screen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nicolamaritan/Repositories/video-streamer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/screen.dir/src/screen.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/screen.dir/src/screen.c.o -MF CMakeFiles/screen.dir/src/screen.c.o.d -o CMakeFiles/screen.dir/src/screen.c.o -c /home/nicolamaritan/Repositories/video-streamer/src/screen.c

CMakeFiles/screen.dir/src/screen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/screen.dir/src/screen.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nicolamaritan/Repositories/video-streamer/src/screen.c > CMakeFiles/screen.dir/src/screen.c.i

CMakeFiles/screen.dir/src/screen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/screen.dir/src/screen.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nicolamaritan/Repositories/video-streamer/src/screen.c -o CMakeFiles/screen.dir/src/screen.c.s

# Object files for target screen
screen_OBJECTS = \
"CMakeFiles/screen.dir/src/screen.c.o"

# External object files for target screen
screen_EXTERNAL_OBJECTS =

libscreen.a: CMakeFiles/screen.dir/src/screen.c.o
libscreen.a: CMakeFiles/screen.dir/build.make
libscreen.a: CMakeFiles/screen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nicolamaritan/Repositories/video-streamer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libscreen.a"
	$(CMAKE_COMMAND) -P CMakeFiles/screen.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/screen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/screen.dir/build: libscreen.a
.PHONY : CMakeFiles/screen.dir/build

CMakeFiles/screen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/screen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/screen.dir/clean

CMakeFiles/screen.dir/depend:
	cd /home/nicolamaritan/Repositories/video-streamer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nicolamaritan/Repositories/video-streamer /home/nicolamaritan/Repositories/video-streamer /home/nicolamaritan/Repositories/video-streamer/build /home/nicolamaritan/Repositories/video-streamer/build /home/nicolamaritan/Repositories/video-streamer/build/CMakeFiles/screen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/screen.dir/depend

