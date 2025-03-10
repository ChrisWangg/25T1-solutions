#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Queue.h"
#include "Stack.h"

struct queue {
	Stack s1;
	Stack s2;
};

Queue QueueNew(void) {
	Queue q = malloc(sizeof(struct queue));
	q->s1 = StackNew();
	q->s2 = StackNew();
	return q;
}

void QueueEnqueue(Queue q, int item) {
    StackPush(q->s1, item);
}

int QueueDequeue(Queue q) {
    if (StackIsEmpty(q->s2)) {
        while (!StackIsEmpty(q->s1)) {
            int item = StackPop(q->s1);
            StackPush(q->s2, item);
        }
    }
    return StackPop(q->s2);
}
bool QueueIsEmpty(Queue q) {
    if (StackIsEmpty(q->s1) && StackIsEmpty(q->s2)) return true;
    return false;
}

void QueueFree(Queue q) {
    StackFree(q->s1);
    StackFree(q->s2);
    free(q);
}