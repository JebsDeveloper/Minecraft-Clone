# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jesper/Desktop/VSCodeProjects/JEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jesper/Desktop/VSCodeProjects/JEngine

# Include any dependencies generated for this target.
include thirdparty/stb_image/CMakeFiles/stb_image.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include thirdparty/stb_image/CMakeFiles/stb_image.dir/compiler_depend.make

# Include the progress variables for this target.
include thirdparty/stb_image/CMakeFiles/stb_image.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/stb_image/CMakeFiles/stb_image.dir/flags.make

thirdparty/stb_image/CMakeFiles/stb_image.dir/codegen:
.PHONY : thirdparty/stb_image/CMakeFiles/stb_image.dir/codegen

thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o: thirdparty/stb_image/CMakeFiles/stb_image.dir/flags.make
thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o: thirdparty/stb_image/src/stb_image.cpp
thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o: thirdparty/stb_image/CMakeFiles/stb_image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/jesper/Desktop/VSCodeProjects/JEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o"
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o -MF CMakeFiles/stb_image.dir/src/stb_image.cpp.o.d -o CMakeFiles/stb_image.dir/src/stb_image.cpp.o -c /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image/src/stb_image.cpp

thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/stb_image.dir/src/stb_image.cpp.i"
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image/src/stb_image.cpp > CMakeFiles/stb_image.dir/src/stb_image.cpp.i

thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/stb_image.dir/src/stb_image.cpp.s"
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image/src/stb_image.cpp -o CMakeFiles/stb_image.dir/src/stb_image.cpp.s

# Object files for target stb_image
stb_image_OBJECTS = \
"CMakeFiles/stb_image.dir/src/stb_image.cpp.o"

# External object files for target stb_image
stb_image_EXTERNAL_OBJECTS =

thirdparty/stb_image/libstb_image.a: thirdparty/stb_image/CMakeFiles/stb_image.dir/src/stb_image.cpp.o
thirdparty/stb_image/libstb_image.a: thirdparty/stb_image/CMakeFiles/stb_image.dir/build.make
thirdparty/stb_image/libstb_image.a: thirdparty/stb_image/CMakeFiles/stb_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/jesper/Desktop/VSCodeProjects/JEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstb_image.a"
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean_target.cmake
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stb_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/stb_image/CMakeFiles/stb_image.dir/build: thirdparty/stb_image/libstb_image.a
.PHONY : thirdparty/stb_image/CMakeFiles/stb_image.dir/build

thirdparty/stb_image/CMakeFiles/stb_image.dir/clean:
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean.cmake
.PHONY : thirdparty/stb_image/CMakeFiles/stb_image.dir/clean

thirdparty/stb_image/CMakeFiles/stb_image.dir/depend:
	cd /Users/jesper/Desktop/VSCodeProjects/JEngine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jesper/Desktop/VSCodeProjects/JEngine /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image /Users/jesper/Desktop/VSCodeProjects/JEngine /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image /Users/jesper/Desktop/VSCodeProjects/JEngine/thirdparty/stb_image/CMakeFiles/stb_image.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : thirdparty/stb_image/CMakeFiles/stb_image.dir/depend

