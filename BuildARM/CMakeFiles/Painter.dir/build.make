# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/swann/SDK/X86/LiteCV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/swann/SDK/X86/LiteCV/BuildARM

# Include any dependencies generated for this target.
include CMakeFiles/Painter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Painter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Painter.dir/flags.make

CMakeFiles/Painter.dir/example/painter/painter.c.o: CMakeFiles/Painter.dir/flags.make
CMakeFiles/Painter.dir/example/painter/painter.c.o: ../example/painter/painter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Painter.dir/example/painter/painter.c.o"
	/home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Painter.dir/example/painter/painter.c.o   -c /home/swann/SDK/X86/LiteCV/example/painter/painter.c

CMakeFiles/Painter.dir/example/painter/painter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Painter.dir/example/painter/painter.c.i"
	/home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/swann/SDK/X86/LiteCV/example/painter/painter.c > CMakeFiles/Painter.dir/example/painter/painter.c.i

CMakeFiles/Painter.dir/example/painter/painter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Painter.dir/example/painter/painter.c.s"
	/home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/swann/SDK/X86/LiteCV/example/painter/painter.c -o CMakeFiles/Painter.dir/example/painter/painter.c.s

CMakeFiles/Painter.dir/example/painter/painter.c.o.requires:

.PHONY : CMakeFiles/Painter.dir/example/painter/painter.c.o.requires

CMakeFiles/Painter.dir/example/painter/painter.c.o.provides: CMakeFiles/Painter.dir/example/painter/painter.c.o.requires
	$(MAKE) -f CMakeFiles/Painter.dir/build.make CMakeFiles/Painter.dir/example/painter/painter.c.o.provides.build
.PHONY : CMakeFiles/Painter.dir/example/painter/painter.c.o.provides

CMakeFiles/Painter.dir/example/painter/painter.c.o.provides.build: CMakeFiles/Painter.dir/example/painter/painter.c.o


# Object files for target Painter
Painter_OBJECTS = \
"CMakeFiles/Painter.dir/example/painter/painter.c.o"

# External object files for target Painter
Painter_EXTERNAL_OBJECTS =

Painter: CMakeFiles/Painter.dir/example/painter/painter.c.o
Painter: CMakeFiles/Painter.dir/build.make
Painter: Litecv/liblicvcore.a
Painter: CMakeFiles/Painter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Painter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Painter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Painter.dir/build: Painter

.PHONY : CMakeFiles/Painter.dir/build

CMakeFiles/Painter.dir/requires: CMakeFiles/Painter.dir/example/painter/painter.c.o.requires

.PHONY : CMakeFiles/Painter.dir/requires

CMakeFiles/Painter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Painter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Painter.dir/clean

CMakeFiles/Painter.dir/depend:
	cd /home/swann/SDK/X86/LiteCV/BuildARM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV/BuildARM /home/swann/SDK/X86/LiteCV/BuildARM /home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles/Painter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Painter.dir/depend

