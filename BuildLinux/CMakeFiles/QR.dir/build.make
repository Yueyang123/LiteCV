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
CMAKE_SOURCE_DIR = /home/swann/LiteCV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/swann/LiteCV/BuildLinux

# Include any dependencies generated for this target.
include CMakeFiles/QR.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/QR.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QR.dir/flags.make

CMakeFiles/QR.dir/example/QR/qr.c.o: CMakeFiles/QR.dir/flags.make
CMakeFiles/QR.dir/example/QR/qr.c.o: ../example/QR/qr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/swann/LiteCV/BuildLinux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/QR.dir/example/QR/qr.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/QR.dir/example/QR/qr.c.o   -c /home/swann/LiteCV/example/QR/qr.c

CMakeFiles/QR.dir/example/QR/qr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/QR.dir/example/QR/qr.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/swann/LiteCV/example/QR/qr.c > CMakeFiles/QR.dir/example/QR/qr.c.i

CMakeFiles/QR.dir/example/QR/qr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/QR.dir/example/QR/qr.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/swann/LiteCV/example/QR/qr.c -o CMakeFiles/QR.dir/example/QR/qr.c.s

# Object files for target QR
QR_OBJECTS = \
"CMakeFiles/QR.dir/example/QR/qr.c.o"

# External object files for target QR
QR_EXTERNAL_OBJECTS =

QR: CMakeFiles/QR.dir/example/QR/qr.c.o
QR: CMakeFiles/QR.dir/build.make
QR: Litecv/liblicvcore.a
QR: Litecv/liblicvimgproc.a
QR: Litecv/liblicvqr.a
QR: ../Litecv/3rd/linux_3rd_lib/jpeg_linux_install/lib/libjpeg.a
QR: ../Litecv/3rd/linux_3rd_lib/png_linux_install/lib/libpng16.a
QR: ../Litecv/3rd/linux_3rd_lib/zlib_linux_install/lib/libz.a
QR: ../Litecv/3rd/linux_3rd_lib/qr_linux_install/lib/libqrencode.a
QR: CMakeFiles/QR.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/swann/LiteCV/BuildLinux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable QR"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QR.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QR.dir/build: QR

.PHONY : CMakeFiles/QR.dir/build

CMakeFiles/QR.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QR.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QR.dir/clean

CMakeFiles/QR.dir/depend:
	cd /home/swann/LiteCV/BuildLinux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swann/LiteCV /home/swann/LiteCV /home/swann/LiteCV/BuildLinux /home/swann/LiteCV/BuildLinux /home/swann/LiteCV/BuildLinux/CMakeFiles/QR.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QR.dir/depend

