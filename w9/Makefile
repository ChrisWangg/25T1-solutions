# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Werror -std=c11

# Target executable
TARGET  = threeSum

# Object files
OBJS    = threeSum.o HashTable.o

# Default rule: build the TARGET
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

threeSum.o: threeSum.c HashTable.h
	$(CC) $(CFLAGS) -c threeSum.c

HashTable.o: HashTable.c HashTable.h
	$(CC) $(CFLAGS) -c HashTable.c

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
