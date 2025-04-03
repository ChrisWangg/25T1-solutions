# ------------------------------------------------------------------------------
# Makefile for isEulerPath
# ------------------------------------------------------------------------------

CC     = gcc
CFLAGS = -Wall -Werror -std=c11

# Default target
all: isEulerPath

# Build the final executable by linking object files
isEulerPath: isEulerPath.o Graph.o
	$(CC) $(CFLAGS) -o isEulerPath isEulerPath.o Graph.o

# Compile Graph.c into Graph.o
Graph.o: Graph.c Graph.h
	$(CC) $(CFLAGS) -c Graph.c

# Compile isEulerPath.c into isEulerPath.o
isEulerPath.o: isEulerPath.c Graph.h
	$(CC) $(CFLAGS) -c isEulerPath.c

# Clean up object files and the executable
clean:
	rm -f *.o isEulerPath
