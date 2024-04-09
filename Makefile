# Executable name
BIN=myls

# Directories
OBJ_DIR=obj
BIN_DIR=bin

# All object files to create (derived from all files in /src)
objs := $(patsubst src/%.cc,%.o,$(wildcard src/*.cc))

# Linker, version, and misc additions
CC=cc
VERSION=-std=c++11

# All call
all: directories program

# Make all of these directories if they don't exist
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# General obj compilation rule
%.o: src/%.cc
	$(CC) $(VERSION) -c src/$*.cc -o $(OBJ_DIR)/$*.o

# Primary source compilation
src_comp: src/*.cc
	make -s $(objs)

# Program binary executable compilation
program: src_comp
	g++ $(OBJ_DIR)/*.o -o $(BIN_DIR)/$(BIN)
