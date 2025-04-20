#include "List.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 8

struct list {
    Item *data;      // 0-based C array
    int size;        // number of elements
    int capacity;    // allocated capacity
};

/** Double the capacity when we run out of space */
static void resize(List list) {
    list->capacity *= 2;
    list->data = realloc(list->data,
                         list->capacity * sizeof *list->data);
    if (!list->data) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
}

List ListNew(void) {
    List list = malloc(sizeof *list);
    if (!list) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    list->size     = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data     = malloc(list->capacity * sizeof *list->data);
    if (!list->data) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return list;
}

void ListFree(List list) {
    free(list->data);
    free(list);
}

void ListAppend(List list, Item it) {
    if (list->size == list->capacity) {
        resize(list);
    }
    list->data[list->size++] = it;
}

Item ListGet(const List list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "error: index %d out of bounds (size = %d)\n",
                index, list->size);
        exit(EXIT_FAILURE);
    }
    return list->data[index];
}

void ListSet(List list, int index, Item it) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "error: index %d out of bounds (size = %d)\n",
                index, list->size);
        exit(EXIT_FAILURE);
    }
    list->data[index] = it;
}

int ListSize(const List list) {
    return list->size;
}
