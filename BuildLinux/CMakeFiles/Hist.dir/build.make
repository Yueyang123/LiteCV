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
CMAKE_BINARY_DIR = /home/swann/SDK/X86/LiteCV/BuildLinux

# Include any dependencies generated for this target.
include CMakeFiles/Hist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Hist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hist.dir/flags.make

CMakeFiles/Hist.dir/example/Hist/Hist.c.o: CMakeFiles/Hist.dir/flags.make
CMakeFiles/Hist.dir/example/Hist/Hist.c.o: ../example/Hist/Hist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/swann/SDK/X86/LiteCV/BuildLinux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Hist.dir/example/Hist/Hist.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Hist.dir/example/Hist/Hist.c.o   -c /home/swann/SDK/X86/LiteCV/example/Hist/Hist.c

CMakeFiles/Hist.dir/example/Hist/Hist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Hist.dir/example/Hist/Hist.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/swann/SDK/X86/LiteCV/example/Hist/Hist.c > CMakeFiles/Hist.dir/example/Hist/Hist.c.i

CMakeFiles/Hist.dir/example/Hist/Hist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Hist.dir/example/Hist/Hist.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/swann/SDK/X86/LiteCV/example/Hist/Hist.c -o CMakeFiles/Hist.dir/example/Hist/Hist.c.s

CMakeFiles/Hist.dir/example/Hist/Hist.c.o.requires:

.PHONY : CMakeFiles/Hist.dir/example/Hist/Hist.c.o.requires

CMakeFiles/Hist.dir/example/Hist/Hist.c.o.provides: CMakeFiles/Hist.dir/example/Hist/Hist.c.o.requires
	$(MAKE) -f CMakeFiles/Hist.dir/build.make CMakeFiles/Hist.dir/example/Hist/Hist.c.o.provides.build
.PHONY : CMakeFiles/Hist.dir/example/Hist/Hist.c.o.provides

CMakeFiles/Hist.dir/example/Hist/Hist.c.o.provides.build: CMakeFiles/Hist.dir/example/Hist/Hist.c.o


# Object files for target Hist
Hist_OBJECTS = \
"CMakeFiles/Hist.dir/example/Hist/Hist.c.o"

# External object files for target Hist
Hist_EXTERNAL_OBJECTS =

Hist: CMakeFiles/Hist.dir/example/Hist/Hist.c.o
Hist: CMakeFiles/Hist.dir/build.make
Hist: Litecv/liblicvcore.a
Hist: Litecv/liblicvimgproc.a
Hist: ../Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a
Hist: ../Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng.a
Hist: ../Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a
Hist: ../Litecv/3rd/linux_3rd_lib/qr_linux_install/lib/libqrencode.a
Hist: CMakeFiles/Hist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/swann/SDK/X86/LiteCV/BuildLinux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Hist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Hist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hist.dir/build: Hist

.PHONY : CMakeFiles/Hist.dir/build

CMakeFiles/Hist.dir/requires: CMakeFiles/Hist.dir/example/Hist/Hist.c.o.requires

.PHONY : CMakeFiles/Hist.dir/requires

CMakeFiles/Hist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Hist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Hist.dir/clean

CMakeFiles/Hist.dir/depend:
	cd /home/swann/SDK/X86/LiteCV/BuildLinux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV /home/swann/SDK/X86/LiteCV/BuildLinux /home/swann/SDK/X86/LiteCV/BuildLinux /home/swann/SDK/X86/LiteCV/BuildLinux/CMakeFiles/Hist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Hist.dir/depend

