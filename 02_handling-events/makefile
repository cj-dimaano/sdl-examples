
# Binary executable
BIN = example02

# Build targets
OBJS = main.cpp

# C-Compiler
CC = clang++

# Compiler options
# -Wall            Print all warnings
# -O3              Maximize optimization for speed
# -I<directory>    Include search directory
OPTS = -Weverything -O3 -I/usr/include

# Libraries
LIB = -lSDL2

# Default make command
all: $(OBJS)
	$(CC) $(OBJS) $(OPTS) $(LIB) -o $(BIN)
