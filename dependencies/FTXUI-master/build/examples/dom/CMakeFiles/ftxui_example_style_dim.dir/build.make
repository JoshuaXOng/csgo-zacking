# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build

# Include any dependencies generated for this target.
include examples/dom/CMakeFiles/ftxui_example_style_dim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/dom/CMakeFiles/ftxui_example_style_dim.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/dom/CMakeFiles/ftxui_example_style_dim.dir/progress.make

# Include the compile flags for this target's objects.
include examples/dom/CMakeFiles/ftxui_example_style_dim.dir/flags.make

examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/flags.make
examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/includes_CXX.rsp
examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj: ../examples/dom/style_dim.cpp
examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom && C:\ProgramData\chocolatey\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj -MF CMakeFiles\ftxui_example_style_dim.dir\style_dim.cpp.obj.d -o CMakeFiles\ftxui_example_style_dim.dir\style_dim.cpp.obj -c C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\dom\style_dim.cpp

examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.i"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom && C:\ProgramData\chocolatey\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\dom\style_dim.cpp > CMakeFiles\ftxui_example_style_dim.dir\style_dim.cpp.i

examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.s"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom && C:\ProgramData\chocolatey\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\dom\style_dim.cpp -o CMakeFiles\ftxui_example_style_dim.dir\style_dim.cpp.s

# Object files for target ftxui_example_style_dim
ftxui_example_style_dim_OBJECTS = \
"CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj"

# External object files for target ftxui_example_style_dim
ftxui_example_style_dim_EXTERNAL_OBJECTS =

examples/dom/ftxui_example_style_dim.exe: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/style_dim.cpp.obj
examples/dom/ftxui_example_style_dim.exe: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/build.make
examples/dom/ftxui_example_style_dim.exe: libftxui-dom.a
examples/dom/ftxui_example_style_dim.exe: libftxui-screen.a
examples/dom/ftxui_example_style_dim.exe: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/linklibs.rsp
examples/dom/ftxui_example_style_dim.exe: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/objects1.rsp
examples/dom/ftxui_example_style_dim.exe: examples/dom/CMakeFiles/ftxui_example_style_dim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftxui_example_style_dim.exe"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ftxui_example_style_dim.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/dom/CMakeFiles/ftxui_example_style_dim.dir/build: examples/dom/ftxui_example_style_dim.exe
.PHONY : examples/dom/CMakeFiles/ftxui_example_style_dim.dir/build

examples/dom/CMakeFiles/ftxui_example_style_dim.dir/clean:
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom && $(CMAKE_COMMAND) -P CMakeFiles\ftxui_example_style_dim.dir\cmake_clean.cmake
.PHONY : examples/dom/CMakeFiles/ftxui_example_style_dim.dir/clean

examples/dom/CMakeFiles/ftxui_example_style_dim.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\dom C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\dom\CMakeFiles\ftxui_example_style_dim.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/dom/CMakeFiles/ftxui_example_style_dim.dir/depend

