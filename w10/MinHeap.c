#include "MinHeap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 8

struct minheap {
    int *data;      // 1-based array
    int size;       // number of elements
    int capacity;   // allocated capacity
};

static void swap(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

static void resize(MinHeap h) {
    h->capacity *= 2;
    h->data = realloc(h->data, (h->capacity + 1) * sizeof *h->data);
    if (!h->data) { perror("realloc"); exit(EXIT_FAILURE); }
}

static void sift_up(MinHeap h, int idx) {
    while (idx > 1 && h->data[idx] < h->data[idx/2]) {
        swap(&h->data[idx], &h->data[idx/2]);
        idx /= 2;
    }
}

static void sift_down(MinHeap h, int idx) {
    int n = h->size;
    while (2*idx <= n) {
        int j = 2*idx;
        if (j < n && h->data[j+1] < h->data[j]) j++;
        if (h->data[idx] <= h->data[j]) break;
        swap(&h->data[idx], &h->data[j]);
        idx = j;
    }
}

MinHeap MinHeapNew(void) {
    MinHeap h = malloc(sizeof *h);
    if (!h) { perror("malloc"); exit(EXIT_FAILURE); }
    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    h->data = malloc((h->capacity + 1) * sizeof *h->data);
    if (!h->data) { perror("malloc"); exit(EXIT_FAILURE); }
    return h;
}

void MinHeapFree(MinHeap h) {
    free(h->data);
    free(h);
}

void MinHeapInsert(MinHeap h, int val) {
    if (h->size == h->capacity) resize(h);
    h->size++;
    h->data[h->size] = val;
    sift_up(h, h->size);
}

int MinHeapPeek(MinHeap h) {
    if (h->size == 0) {
        fprintf(stderr, "error: heap is empty\n");
        exit(EXIT_FAILURE);
    }
    return h->data[1];
}

int MinHeapDeleteMin(MinHeap h) {
    if (h->size == 0) {
        fprintf(stderr, "error: heap is empty\n");
        exit(EXIT_FAILURE);
    }
    int ret = h->data[1];
    h->data[1] = h->data[h->size--];
    sift_down(h, 1);
    return ret;
}

int MinHeapSize(MinHeap h) {
    return h->size;
}

bool MinHeapEmpty(MinHeap h) {
    if (h->size == 0) return true;
    return false;
}