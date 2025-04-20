#include <stdbool.h>
#ifndef MINHEAP_H
#define MINHEAP_H

typedef struct minheap *MinHeap;

/** Create a new empty min‑heap */
MinHeap MinHeapNew(void);

/** Free all memory used by the heap */
void MinHeapFree(MinHeap h);

/** Insert a value into the heap */
void MinHeapInsert(MinHeap h, int val);

/** Return (but do not remove) the smallest value */
int MinHeapPeek(MinHeap h);

/** Remove and return the smallest value */
int MinHeapDeleteMin(MinHeap h);

/** Return the size of the min heap */
int MinHeapSize(MinHeap h);

/** Return true if heap is empty */
bool MinHeapEmpty(MinHeap h);

#endif /* MINHEAP_H */
