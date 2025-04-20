#ifndef LIST_H
#define LIST_H

typedef int Item;      // change to whatever type you need

typedef struct list *List;

/** Create a new empty List */
List ListNew(void);

/** Free all memory used by the list */
void ListFree(List list);

/** Append an item to the end */
void ListAppend(List list, Item it);

/** Get the item at index (0 ≤ index < size) */
Item ListGet(const List list, int index);

/** Set the item at index (0 ≤ index < size) */
void ListSet(List list, int index, Item it);

/** Return the number of items currently in the list */
int ListSize(const List list);

#endif /* LIST_H */
