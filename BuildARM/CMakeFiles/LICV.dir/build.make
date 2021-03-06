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
include CMakeFiles/LICV.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LICV.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LICV.dir/flags.make

CMakeFiles/LICV.dir/main.c.o: CMakeFiles/LICV.dir/flags.make
CMakeFiles/LICV.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/LICV.dir/main.c.o"
	/home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LICV.dir/main.c.o   -c /home/swann/SDK/X86/LiteCV/main.c

CMakeFiles/LICV.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LICV.dir/main.c.i"
	/home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/swann/SDK/X86/LiteCV/main.c > CMakeFiles/LICV.dir/main.c.i

CMakeFiles/LICV.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LICV.dir/main.c.s"
	/home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/swann/SDK/X86/LiteCV/main.c -o CMakeFiles/LICV.dir/main.c.s

CMakeFiles/LICV.dir/main.c.o.requires:

.PHONY : CMakeFiles/LICV.dir/main.c.o.requires

CMakeFiles/LICV.dir/main.c.o.provides: CMakeFiles/LICV.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/LICV.dir/build.make CMakeFiles/LICV.dir/main.c.o.provides.build
.PHONY : CMakeFiles/LICV.dir/main.c.o.provides

CMakeFiles/LICV.dir/main.c.o.provides.build: CMakeFiles/LICV.dir/main.c.o


# Object files for target LICV
LICV_OBJECTS = \
"CMakeFiles/LICV.dir/main.c.o"

# External object files for target LICV
LICV_EXTERNAL_OBJECTS =

LICV: CMakeFiles/LICV.dir/main.c.o
LICV: CMakeFiles/LICV.dir/build.make
LICV: Litecv/liblicvcore.a
LICV: Litecv/liblicvimgproc.a
LICV: ../Litecv/3rd/arm_3rd_lib/jpeg_arm_install/lib/libjpeg.a
LICV: ../Litecv/3rd/arm_3rd_lib/png_arm_install/lib/libpng.a
LICV: ../Litecv/3rd/arm_3rd_lib/zlib_arm_install/lib/libz.a
LICV: ../Litecv/3rd/arm_3rd_lib/qr_arm_install/lib/libqrencode.a
LICV: CMakeFiles/LICV.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable LICV"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LICV.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LICV.dir/build: LICV

.PHONY : CMakeFiles/LICV.dir/build

CMakeFiles/LICV.dir/requires: CMakeFiles/LICV.dir/main.c.o.requires

.PHONY : CMakeFiles/LICV.dir/requires

CMakeFiles/LICV.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LICV.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LICV.dir/clean

CMakeFiles/LICV.dir/depend:
	cd /home/swann/SDK/X86/LiteCV/BuildARM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV/BuildARM /home/swann/SDK/X86/LiteCV/BuildARM /home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles/LICV.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LICV.dir/depend

