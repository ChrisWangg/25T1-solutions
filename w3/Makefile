# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -O2

# Default target
all: isStableSort selectionSort

# Build isStableSort executable
isStableSort: isStableSort.c
	$(CC) $(CFLAGS) isStableSort.c -o isStableSort

# Build selectionSort executable
selectionSort: selectionSort.c
	$(CC) $(CFLAGS) selectionSort.c -o selectionSort

# Clean up
clean:
	rm -f isStableSort selectionSort
