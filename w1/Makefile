# Makefile for compiling listCode.c and swap.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRC_LIST = listCode.c
SRC_SWAP = swap.c

# Output executables
OUT_LIST = listCode
OUT_SWAP = swap

# Default target
all: $(OUT_LIST) $(OUT_SWAP)

# Rule to compile listCode.c into an executable
$(OUT_LIST): $(SRC_LIST)
	$(CC) $(CFLAGS) -o $(OUT_LIST) $(SRC_LIST)

# Rule to compile swap.c into an executable
$(OUT_SWAP): $(SRC_SWAP)
	$(CC) $(CFLAGS) -o $(OUT_SWAP) $(SRC_SWAP)

# Clean target to remove the executables
clean:
	rm -f $(OUT_LIST) $(OUT_SWAP)

# PHONY targets
.PHONY: all clean