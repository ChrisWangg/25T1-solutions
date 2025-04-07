#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

struct SetRep {
    int *elems;
    int maxSize;
    int nelems;
};

Set SetNew(int maxSize) {
    Set s = malloc(sizeof(struct SetRep));
    s->elems = malloc(maxSize * sizeof(int));
    s->maxSize = maxSize;
    s->nelems = 0;
    return s;
}

void SetFree(Set s) {
    free(s->elems);
    free(s);
}

void SetInsert(Set s, int elem) {
    if (!SetContains(s, elem)) {
        if (s->nelems < s->maxSize) {
            s->elems[s->nelems++] = elem;
        } else {
            fprintf(stderr, "Set is full\n");
            exit(1);
        }
    }
}

int SetContains(Set s, int elem) {
    for (int i = 0; i < s->nelems; i++) {
        if (s->elems[i] == elem) {
            return 1;
        }
    }
    return 0;
}

void SetShow(Set s) {
    printf("{ ");
    for (int i = 0; i < s->nelems; i++) {
        printf("%d ", s->elems[i]);
    }
    printf("}\n");
}