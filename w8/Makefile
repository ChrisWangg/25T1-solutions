###############################################################################
# Makefile
#
# This Makefile compiles all .c files into object files, then links them into
# a single executable named 'test'. Adjust the target or filenames as needed.
###############################################################################

CC     = gcc
CFLAGS = -Wall -Werror -std=c11

# Object files for the Graph, Set, and reachable modules.
OBJS   = Graph.o Set.o reachable.o

# Test object file from testReachable.c
TEST_OBJS = testReachable.o

# Default target: build the 'test' executable.
all: test

# Link step: combine the test object file with the other objects.
test: $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o testReachable $(TEST_OBJS) $(OBJS)

# Compile testReachable.c into testReachable.o.
testReachable.o: testReachable.c Graph.h Set.h
	$(CC) $(CFLAGS) -c testReachable.c

# Compile Graph.c
Graph.o: Graph.c Graph.h
	$(CC) $(CFLAGS) -c Graph.c

# Compile Set.c
Set.o: Set.c Set.h
	$(CC) $(CFLAGS) -c Set.c

# Compile reachable.c
reachable.o: Reachable.c Graph.h Set.h
	$(CC) $(CFLAGS) -c Reachable.c

# Clean up the build artifacts.
clean:
	rm -f *.o testReachable
