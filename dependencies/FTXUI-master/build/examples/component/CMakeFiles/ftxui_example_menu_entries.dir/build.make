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
include examples/component/CMakeFiles/ftxui_example_menu_entries.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/component/CMakeFiles/ftxui_example_menu_entries.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/component/CMakeFiles/ftxui_example_menu_entries.dir/progress.make

# Include the compile flags for this target's objects.
include examples/component/CMakeFiles/ftxui_example_menu_entries.dir/flags.make

examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/flags.make
examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/includes_CXX.rsp
examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj: ../examples/component/menu_entries.cpp
examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component && C:\ProgramData\chocolatey\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj -MF CMakeFiles\ftxui_example_menu_entries.dir\menu_entries.cpp.obj.d -o CMakeFiles\ftxui_example_menu_entries.dir\menu_entries.cpp.obj -c C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\component\menu_entries.cpp

examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.i"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component && C:\ProgramData\chocolatey\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\component\menu_entries.cpp > CMakeFiles\ftxui_example_menu_entries.dir\menu_entries.cpp.i

examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.s"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component && C:\ProgramData\chocolatey\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\component\menu_entries.cpp -o CMakeFiles\ftxui_example_menu_entries.dir\menu_entries.cpp.s

# Object files for target ftxui_example_menu_entries
ftxui_example_menu_entries_OBJECTS = \
"CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj"

# External object files for target ftxui_example_menu_entries
ftxui_example_menu_entries_EXTERNAL_OBJECTS =

examples/component/ftxui_example_menu_entries.exe: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/menu_entries.cpp.obj
examples/component/ftxui_example_menu_entries.exe: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/build.make
examples/component/ftxui_example_menu_entries.exe: libftxui-component.a
examples/component/ftxui_example_menu_entries.exe: libftxui-dom.a
examples/component/ftxui_example_menu_entries.exe: libftxui-screen.a
examples/component/ftxui_example_menu_entries.exe: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/linklibs.rsp
examples/component/ftxui_example_menu_entries.exe: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/objects1.rsp
examples/component/ftxui_example_menu_entries.exe: examples/component/CMakeFiles/ftxui_example_menu_entries.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftxui_example_menu_entries.exe"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ftxui_example_menu_entries.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/component/CMakeFiles/ftxui_example_menu_entries.dir/build: examples/component/ftxui_example_menu_entries.exe
.PHONY : examples/component/CMakeFiles/ftxui_example_menu_entries.dir/build

examples/component/CMakeFiles/ftxui_example_menu_entries.dir/clean:
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component && $(CMAKE_COMMAND) -P CMakeFiles\ftxui_example_menu_entries.dir\cmake_clean.cmake
.PHONY : examples/component/CMakeFiles/ftxui_example_menu_entries.dir/clean

examples/component/CMakeFiles/ftxui_example_menu_entries.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\examples\component C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\examples\component\CMakeFiles\ftxui_example_menu_entries.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/component/CMakeFiles/ftxui_example_menu_entries.dir/depend

