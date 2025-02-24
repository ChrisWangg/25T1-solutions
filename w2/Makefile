# -----------------------------------------------------------------------------
# Makefile for compiling multiple C programs
# -----------------------------------------------------------------------------

# The compiler to use
CC = gcc

# Compilation flags: -Wall (all warnings), -Wextra (additional warnings), etc.
CFLAGS = -Wall -Wextra -O2

# List of all executables to build
PROGRAMS = palindrome recListCode towerOfHanoi twoSum

# Default target: build all programs
all: $(PROGRAMS)

# -----------------------------------------------------------------------------
# Rules for building each program
# -----------------------------------------------------------------------------

palindrome: palindrome.c
	$(CC) $(CFLAGS) -o $@ $^

recListCode: recListCode.c
	$(CC) $(CFLAGS) -o $@ $^

towerOfHanoi: towerOfHanoi.c
	$(CC) $(CFLAGS) -o $@ $^

twoSum: twoSum.c
	$(CC) $(CFLAGS) -o $@ $^

# -----------------------------------------------------------------------------
# Clean up build files
# -----------------------------------------------------------------------------
clean:
	rm -f $(PROGRAMS)
