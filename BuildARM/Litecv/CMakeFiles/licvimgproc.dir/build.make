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
include Litecv/CMakeFiles/licvimgproc.dir/depend.make

# Include the progress variables for this target.
include Litecv/CMakeFiles/licvimgproc.dir/progress.make

# Include the compile flags for this target's objects.
include Litecv/CMakeFiles/licvimgproc.dir/flags.make

Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o: Litecv/CMakeFiles/licvimgproc.dir/flags.make
Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o: ../Litecv/Imgproc/li_image_proc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o"
	cd /home/swann/SDK/X86/LiteCV/BuildARM/Litecv && /home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o   -c /home/swann/SDK/X86/LiteCV/Litecv/Imgproc/li_image_proc.c

Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.i"
	cd /home/swann/SDK/X86/LiteCV/BuildARM/Litecv && /home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/swann/SDK/X86/LiteCV/Litecv/Imgproc/li_image_proc.c > CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.i

Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.s"
	cd /home/swann/SDK/X86/LiteCV/BuildARM/Litecv && /home/swann/SDK/IMX_283A/CrossCompile/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/swann/SDK/X86/LiteCV/Litecv/Imgproc/li_image_proc.c -o CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.s

Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.requires:

.PHONY : Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.requires

Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.provides: Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.requires
	$(MAKE) -f Litecv/CMakeFiles/licvimgproc.dir/build.make Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.provides.build
.PHONY : Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.provides

Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.provides.build: Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o


# Object files for target licvimgproc
licvimgproc_OBJECTS = \
"CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o"

# External object files for target licvimgproc
licvimgproc_EXTERNAL_OBJECTS =

Litecv/liblicvimgproc.a: Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o
Litecv/liblicvimgproc.a: Litecv/CMakeFiles/licvimgproc.dir/build.make
Litecv/liblicvimgproc.a: Litecv/CMakeFiles/licvimgproc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/swann/SDK/X86/LiteCV/BuildARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library liblicvimgproc.a"
	cd /home/swann/SDK/X86/LiteCV/BuildARM/Litecv && $(CMAKE_COMMAND) -P CMakeFiles/licvimgproc.dir/cmake_clean_target.cmake
	cd /home/swann/SDK/X86/LiteCV/BuildARM/Litecv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/licvimgproc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Litecv/CMakeFiles/licvimgproc.dir/build: Litecv/liblicvimgproc.a

.PHONY : Litecv/CMakeFiles/licvimgproc.dir/build

Litecv/CMakeFiles/licvimgproc.dir/requires: Litecv/CMakeFiles/licvimgproc.dir/Imgproc/li_image_proc.c.o.requires

.PHONY : Litecv/CMakeFiles/licvimgproc.dir/requires

Litecv/CMakeFiles/licvimgproc.dir/clean:
	cd /home/swann/SDK/X86/LiteCV/BuildARM/Litecv && $(CMAKE_COMMAND) -P CMakeFiles/licvimgproc.dir/cmake_clean.cmake
.PHONY : Litecv/CMakeFiles/licvimgproc.dir/clean

Litecv/CMakeFiles/licvimgproc.dir/depend:
	cd /home/swann/SDK/X86/LiteCV/BuildARM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV/Litecv /home/swann/SDK/X86/LiteCV/BuildARM /home/swann/SDK/X86/LiteCV/BuildARM/Litecv /home/swann/SDK/X86/LiteCV/BuildARM/Litecv/CMakeFiles/licvimgproc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Litecv/CMakeFiles/licvimgproc.dir/depend

