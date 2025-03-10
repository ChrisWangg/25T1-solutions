#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

// Definition of the node structure
struct node {
    int data;
    struct node *next;
};

// Definition of the stack structure
struct stack {
    struct node *top;
    int size;
};

typedef struct node* Node;
typedef struct stack* Stack;

// Creates a new empty stack
Stack StackNew(void) {
    Stack s = malloc(sizeof(struct stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    s->top = NULL;
    s->size = 0;
    return s;
}

// Pushes an item onto the stack
void StackPush(Stack s, int item) {
    Node newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = item;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

// Pops an item from the stack and returns it
// Assumes that the stack is not empty
int StackPop(Stack s) {
    if (s->top == NULL) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    Node temp = s->top;
    int poppedItem = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return poppedItem;
}

// Returns the number of items on the stack
int StackSize(Stack s) {
    return s->size;
}

// Returns whether the stack is empty
bool StackIsEmpty(Stack s) {
    if (s->size == 0) return true;
    return false;
}

// Frees the stack
void StackFree(Stack s) {
    while (s->top != NULL) {
        Node temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
}
