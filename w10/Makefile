# Makefile

# Compiler and flags
CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -g

# Source files
SRCS    = List.c MinHeap.c kLargestValues.c

# Object files
OBJS    = $(SRCS:.c=.o)

# Final executable
TARGET  = kLargestValues

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Generic rule for .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
