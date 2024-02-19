# Makefile for Mario remake

# Compiler and flags
CC = g++
CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs) -lSDL2_Image
INCLUDE_FLAGS = -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = bin

# Files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

# Executable Name
EXEC = MarioGame

all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) $(INCLUDE_FLAGS) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN_DIR)/$(EXEC)