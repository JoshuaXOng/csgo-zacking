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

# Utility rule file for doc.

# Include any custom commands dependencies for this target.
include doc/CMakeFiles/doc.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/CMakeFiles/doc.dir/progress.make

doc/CMakeFiles/doc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating API documentation with Doxygen"
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\doc && C:\ProgramData\chocolatey\bin\doxygen.exe C:/Users/jxo/Desktop/CodingRepos/Personal/csgo-zacking/dependencies/FTXUI-master/build/doc/Doxyfile

doc: doc/CMakeFiles/doc
doc: doc/CMakeFiles/doc.dir/build.make
.PHONY : doc

# Rule to build all files generated by this target.
doc/CMakeFiles/doc.dir/build: doc
.PHONY : doc/CMakeFiles/doc.dir/build

doc/CMakeFiles/doc.dir/clean:
	cd /d C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\doc && $(CMAKE_COMMAND) -P CMakeFiles\doc.dir\cmake_clean.cmake
.PHONY : doc/CMakeFiles/doc.dir/clean

doc/CMakeFiles/doc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\doc C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\doc C:\Users\jxo\Desktop\CodingRepos\Personal\csgo-zacking\dependencies\FTXUI-master\build\doc\CMakeFiles\doc.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/doc.dir/depend
