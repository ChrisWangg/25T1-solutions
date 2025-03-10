CC     = gcc
CFLAGS = -Wall -Werror -std=c11

# Build both tests by default
all: QueueTest BSTTest

# -----------------------
# QueueTest
# -----------------------
QueueTest: QueueTest.o Queue.o Stack.o
	$(CC) $(CFLAGS) -o QueueTest QueueTest.o Queue.o Stack.o

QueueTest.o: QueueTest.c Queue.h Stack.h
	$(CC) $(CFLAGS) -c QueueTest.c

Queue.o: Queue.c Queue.h Stack.h
	$(CC) $(CFLAGS) -c Queue.c

Stack.o: Stack.c Stack.h
	$(CC) $(CFLAGS) -c Stack.c

# -----------------------
# BSTTest
# -----------------------
BSTTest: BSTTest.o
	$(CC) $(CFLAGS) -o BSTTest BSTTest.o

BSTTest.o: BSTTest.c
	$(CC) $(CFLAGS) -c BSTTest.c

# -----------------------
# Cleanup
# -----------------------
clean:
	rm -f *.o QueueTest BSTTest
