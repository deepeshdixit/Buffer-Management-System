# Compiler and flags for macOS
CPP = g++
INC = -I./include
FLAGS = -std=c++20 -fdiagnostics-color=always -Wall
DEV = $(FLAGS) -g -fsanitize=address
OPT = $(FLAGS) -O3

# Executable file paths
BIN_DEV = ./bin/debug
BIN_OPT = ./bin/opt

# Object file paths
OBJ_DEV = ./obj/debug
OBJ_OPT = ./obj/opt

# Source files are now in the include directory
SRC_JOIN = ./include/join.cpp
SRC_SELECT = ./include/select.cpp
SRC_TEST = ./include/test.cpp
SRC_TABLE = ./include/table.cpp
SRC_UNTABLE = ./include/untable.cpp
SRC_DM = ./include/DiskManager.cpp
SRC_PAGE = ./include/Page.cpp

# Target executables
EXE_JOIN_DEV = $(BIN_DEV)/join
EXE_SELECT_DEV = $(BIN_DEV)/select
EXE_TEST_DEV = $(BIN_DEV)/test

EXE_JOIN_OPT = $(BIN_OPT)/join
EXE_SELECT_OPT = $(BIN_OPT)/select
EXE_TEST_OPT = $(BIN_OPT)/test
EXE_TABLE_OPT = $(BIN_OPT)/table
EXE_UNTABLE_OPT = $(BIN_OPT)/untable

# Dependent objects
DEP_OBJ_OPT = $(OBJ_OPT)/DiskManager.o $(OBJ_OPT)/Page.o
DEP_OBJ_DEV = $(OBJ_DEV)/DiskManager.o $(OBJ_DEV)/Page.o

.PHONY: all clean run_join run_select run_join_dev run_select_dev table untable

all: $(EXE_JOIN_OPT) $(EXE_SELECT_OPT) $(EXE_TEST_OPT) $(EXE_TABLE_OPT) $(EXE_UNTABLE_OPT)

# Build rules for optimized versions
$(EXE_JOIN_OPT): $(DEP_OBJ_OPT) $(OBJ_OPT)/join.o | $(BIN_OPT)
	$(CPP) $(DEP_OBJ_OPT) $(OBJ_OPT)/join.o $(OPT) -o $@

$(EXE_SELECT_OPT): $(DEP_OBJ_OPT) $(OBJ_OPT)/select.o | $(BIN_OPT)
	$(CPP) $(DEP_OBJ_OPT) $(OBJ_OPT)/select.o $(OPT) -o $@

$(EXE_TEST_OPT): $(DEP_OBJ_OPT) $(OBJ_OPT)/test.o | $(BIN_OPT)
	$(CPP) $(DEP_OBJ_OPT) $(OBJ_OPT)/test.o $(OPT) -o $@

$(EXE_TABLE_OPT): $(DEP_OBJ_OPT) $(OBJ_OPT)/table.o | $(BIN_OPT)
	$(CPP) $(DEP_OBJ_OPT) $(OBJ_OPT)/table.o $(OPT) -o $@

$(EXE_UNTABLE_OPT): $(DEP_OBJ_OPT) $(OBJ_OPT)/untable.o | $(BIN_OPT)
	$(CPP) $(DEP_OBJ_OPT) $(OBJ_OPT)/untable.o $(OPT) -o $@

# Build rules for debug versions
$(EXE_JOIN_DEV): $(DEP_OBJ_DEV) $(OBJ_DEV)/join.o | $(BIN_DEV)
	$(CPP) $(DEP_OBJ_DEV) $(OBJ_DEV)/join.o $(DEV) -o $@

$(EXE_SELECT_DEV): $(DEP_OBJ_DEV) $(OBJ_DEV)/select.o | $(BIN_DEV)
	$(CPP) $(DEP_OBJ_DEV) $(OBJ_DEV)/select.o $(DEV) -o $@

$(EXE_TEST_DEV): $(DEP_OBJ_DEV) $(OBJ_DEV)/test.o | $(BIN_DEV)
	$(CPP) $(DEP_OBJ_DEV) $(OBJ_DEV)/test.o $(DEV) -o $@

# Pattern rules for compilation
$(OBJ_DEV)/%.o: ./include/%.cpp | $(OBJ_DEV)
	$(CPP) $(DEV) $(INC) -c $< -o $@

$(OBJ_OPT)/%.o: ./include/%.cpp | $(OBJ_OPT)
	$(CPP) $(OPT) $(INC) -c $< -o $@

# Directory creation rules
$(BIN_OPT):
	mkdir -p $(BIN_OPT)

$(BIN_DEV):
	mkdir -p $(BIN_DEV)

$(OBJ_OPT):
	mkdir -p $(OBJ_OPT)

$(OBJ_DEV):
	mkdir -p $(OBJ_DEV)

# Run targets
run_join: $(EXE_JOIN_OPT)
	$(EXE_JOIN_OPT) 2> ./logs/join.log

run_join_dev: $(EXE_JOIN_DEV)
	$(EXE_JOIN_DEV) 2> ./logs/join.log

run_select: $(EXE_SELECT_OPT)
	$(EXE_SELECT_OPT) 2> ./logs/select.log

run_select_dev: $(EXE_SELECT_DEV)
	$(EXE_SELECT_DEV) 2> ./logs/select.log

table: $(EXE_TABLE_OPT)
	$(EXE_TABLE_OPT)

untable: $(EXE_UNTABLE_OPT)
	$(EXE_UNTABLE_OPT)

clean:
	rm -rf $(BIN_OPT) $(BIN_DEV) $(OBJ_OPT) $(OBJ_DEV) *.exe *.o