# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /Users/assiamegnounif/Downloads/MCTS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/assiamegnounif/Downloads/MCTS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/assiamegnounif/Downloads/MCTS/CMakeFiles /Users/assiamegnounif/Downloads/MCTS//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/assiamegnounif/Downloads/MCTS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Arene_light

# Build rule for target.
Arene_light: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Arene_light
.PHONY : Arene_light

# fast build rule for target.
Arene_light/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/build
.PHONY : Arene_light/fast

#=============================================================================
# Target rules for targets named joueurs

# Build rule for target.
joueurs: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 joueurs
.PHONY : joueurs

# fast build rule for target.
joueurs/fast:
	$(MAKE) $(MAKESILENT) -f joueurs/CMakeFiles/joueurs.dir/build.make joueurs/CMakeFiles/joueurs.dir/build
.PHONY : joueurs/fast

arbitre.o: arbitre.cpp.o
.PHONY : arbitre.o

# target to build an object file
arbitre.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/arbitre.cpp.o
.PHONY : arbitre.cpp.o

arbitre.i: arbitre.cpp.i
.PHONY : arbitre.i

# target to preprocess a source file
arbitre.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/arbitre.cpp.i
.PHONY : arbitre.cpp.i

arbitre.s: arbitre.cpp.s
.PHONY : arbitre.s

# target to generate assembly for a file
arbitre.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/arbitre.cpp.s
.PHONY : arbitre.cpp.s

jeu.o: jeu.cpp.o
.PHONY : jeu.o

# target to build an object file
jeu.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/jeu.cpp.o
.PHONY : jeu.cpp.o

jeu.i: jeu.cpp.i
.PHONY : jeu.i

# target to preprocess a source file
jeu.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/jeu.cpp.i
.PHONY : jeu.cpp.i

jeu.s: jeu.cpp.s
.PHONY : jeu.s

# target to generate assembly for a file
jeu.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/jeu.cpp.s
.PHONY : jeu.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Arene_light.dir/build.make CMakeFiles/Arene_light.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Arene_light"
	@echo "... joueurs"
	@echo "... arbitre.o"
	@echo "... arbitre.i"
	@echo "... arbitre.s"
	@echo "... jeu.o"
	@echo "... jeu.i"
	@echo "... jeu.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

