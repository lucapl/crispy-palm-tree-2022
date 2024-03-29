# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucas/Desktop/co_project_final/crispy-palm-tree-2022-genetic-update

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/Desktop/co_project_final/crispy-palm-tree-2022-genetic-update

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lucas/Desktop/co_project_final/crispy-palm-tree-2022-genetic-update/CMakeFiles /home/lucas/Desktop/co_project_final/crispy-palm-tree-2022-genetic-update/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lucas/Desktop/co_project_final/crispy-palm-tree-2022-genetic-update/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named co_proj

# Build rule for target.
co_proj: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 co_proj
.PHONY : co_proj

# fast build rule for target.
co_proj/fast:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/build
.PHONY : co_proj/fast

src/books.o: src/books.cpp.o

.PHONY : src/books.o

# target to build an object file
src/books.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/books.cpp.o
.PHONY : src/books.cpp.o

src/books.i: src/books.cpp.i

.PHONY : src/books.i

# target to preprocess a source file
src/books.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/books.cpp.i
.PHONY : src/books.cpp.i

src/books.s: src/books.cpp.s

.PHONY : src/books.s

# target to generate assembly for a file
src/books.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/books.cpp.s
.PHONY : src/books.cpp.s

src/clustering.o: src/clustering.cpp.o

.PHONY : src/clustering.o

# target to build an object file
src/clustering.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/clustering.cpp.o
.PHONY : src/clustering.cpp.o

src/clustering.i: src/clustering.cpp.i

.PHONY : src/clustering.i

# target to preprocess a source file
src/clustering.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/clustering.cpp.i
.PHONY : src/clustering.cpp.i

src/clustering.s: src/clustering.cpp.s

.PHONY : src/clustering.s

# target to generate assembly for a file
src/clustering.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/clustering.cpp.s
.PHONY : src/clustering.cpp.s

src/geneticAlgorithm.o: src/geneticAlgorithm.cpp.o

.PHONY : src/geneticAlgorithm.o

# target to build an object file
src/geneticAlgorithm.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/geneticAlgorithm.cpp.o
.PHONY : src/geneticAlgorithm.cpp.o

src/geneticAlgorithm.i: src/geneticAlgorithm.cpp.i

.PHONY : src/geneticAlgorithm.i

# target to preprocess a source file
src/geneticAlgorithm.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/geneticAlgorithm.cpp.i
.PHONY : src/geneticAlgorithm.cpp.i

src/geneticAlgorithm.s: src/geneticAlgorithm.cpp.s

.PHONY : src/geneticAlgorithm.s

# target to generate assembly for a file
src/geneticAlgorithm.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/geneticAlgorithm.cpp.s
.PHONY : src/geneticAlgorithm.cpp.s

src/libraries.o: src/libraries.cpp.o

.PHONY : src/libraries.o

# target to build an object file
src/libraries.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/libraries.cpp.o
.PHONY : src/libraries.cpp.o

src/libraries.i: src/libraries.cpp.i

.PHONY : src/libraries.i

# target to preprocess a source file
src/libraries.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/libraries.cpp.i
.PHONY : src/libraries.cpp.i

src/libraries.s: src/libraries.cpp.s

.PHONY : src/libraries.s

# target to generate assembly for a file
src/libraries.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/libraries.cpp.s
.PHONY : src/libraries.cpp.s

src/library.o: src/library.cpp.o

.PHONY : src/library.o

# target to build an object file
src/library.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/library.cpp.o
.PHONY : src/library.cpp.o

src/library.i: src/library.cpp.i

.PHONY : src/library.i

# target to preprocess a source file
src/library.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/library.cpp.i
.PHONY : src/library.cpp.i

src/library.s: src/library.cpp.s

.PHONY : src/library.s

# target to generate assembly for a file
src/library.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/library.cpp.s
.PHONY : src/library.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/randomizer.o: src/randomizer.cpp.o

.PHONY : src/randomizer.o

# target to build an object file
src/randomizer.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/randomizer.cpp.o
.PHONY : src/randomizer.cpp.o

src/randomizer.i: src/randomizer.cpp.i

.PHONY : src/randomizer.i

# target to preprocess a source file
src/randomizer.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/randomizer.cpp.i
.PHONY : src/randomizer.cpp.i

src/randomizer.s: src/randomizer.cpp.s

.PHONY : src/randomizer.s

# target to generate assembly for a file
src/randomizer.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/randomizer.cpp.s
.PHONY : src/randomizer.cpp.s

src/solution.o: src/solution.cpp.o

.PHONY : src/solution.o

# target to build an object file
src/solution.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/solution.cpp.o
.PHONY : src/solution.cpp.o

src/solution.i: src/solution.cpp.i

.PHONY : src/solution.i

# target to preprocess a source file
src/solution.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/solution.cpp.i
.PHONY : src/solution.cpp.i

src/solution.s: src/solution.cpp.s

.PHONY : src/solution.s

# target to generate assembly for a file
src/solution.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/solution.cpp.s
.PHONY : src/solution.cpp.s

src/solutionPool.o: src/solutionPool.cpp.o

.PHONY : src/solutionPool.o

# target to build an object file
src/solutionPool.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/solutionPool.cpp.o
.PHONY : src/solutionPool.cpp.o

src/solutionPool.i: src/solutionPool.cpp.i

.PHONY : src/solutionPool.i

# target to preprocess a source file
src/solutionPool.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/solutionPool.cpp.i
.PHONY : src/solutionPool.cpp.i

src/solutionPool.s: src/solutionPool.cpp.s

.PHONY : src/solutionPool.s

# target to generate assembly for a file
src/solutionPool.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/solutionPool.cpp.s
.PHONY : src/solutionPool.cpp.s

src/sus.o: src/sus.cpp.o

.PHONY : src/sus.o

# target to build an object file
src/sus.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/sus.cpp.o
.PHONY : src/sus.cpp.o

src/sus.i: src/sus.cpp.i

.PHONY : src/sus.i

# target to preprocess a source file
src/sus.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/sus.cpp.i
.PHONY : src/sus.cpp.i

src/sus.s: src/sus.cpp.s

.PHONY : src/sus.s

# target to generate assembly for a file
src/sus.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/sus.cpp.s
.PHONY : src/sus.cpp.s

src/timer.o: src/timer.cpp.o

.PHONY : src/timer.o

# target to build an object file
src/timer.cpp.o:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/timer.cpp.o
.PHONY : src/timer.cpp.o

src/timer.i: src/timer.cpp.i

.PHONY : src/timer.i

# target to preprocess a source file
src/timer.cpp.i:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/timer.cpp.i
.PHONY : src/timer.cpp.i

src/timer.s: src/timer.cpp.s

.PHONY : src/timer.s

# target to generate assembly for a file
src/timer.cpp.s:
	$(MAKE) -f CMakeFiles/co_proj.dir/build.make CMakeFiles/co_proj.dir/src/timer.cpp.s
.PHONY : src/timer.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... co_proj"
	@echo "... src/books.o"
	@echo "... src/books.i"
	@echo "... src/books.s"
	@echo "... src/clustering.o"
	@echo "... src/clustering.i"
	@echo "... src/clustering.s"
	@echo "... src/geneticAlgorithm.o"
	@echo "... src/geneticAlgorithm.i"
	@echo "... src/geneticAlgorithm.s"
	@echo "... src/libraries.o"
	@echo "... src/libraries.i"
	@echo "... src/libraries.s"
	@echo "... src/library.o"
	@echo "... src/library.i"
	@echo "... src/library.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/randomizer.o"
	@echo "... src/randomizer.i"
	@echo "... src/randomizer.s"
	@echo "... src/solution.o"
	@echo "... src/solution.i"
	@echo "... src/solution.s"
	@echo "... src/solutionPool.o"
	@echo "... src/solutionPool.i"
	@echo "... src/solutionPool.s"
	@echo "... src/sus.o"
	@echo "... src/sus.i"
	@echo "... src/sus.s"
	@echo "... src/timer.o"
	@echo "... src/timer.i"
	@echo "... src/timer.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

