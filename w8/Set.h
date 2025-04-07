#ifndef SET_H
#define SET_H

typedef struct SetRep *Set;

/**
 * Creates a new empty set with a specified maximum size.
 *
 * @param maxSize The maximum number of elements the set can hold.
 * @return A new Set instance.
 */
Set SetNew(int maxSize);

/**
 * Frees all memory associated with the set.
 *
 * @param s The set to dispose of.
 */
void SetFree(Set s);

/**
 * Inserts an element into the set if it's not already present.
 *
 * @param s The set to insert the element into.
 * @param elem The element to be inserted.
 */
void SetInsert(Set s, int elem);

/**
 * Checks if an element is a member of the set.
 *
 * @param s The set to check for membership.
 * @param elem The element to check for.
 * @return 1 if the element is in the set, 0 otherwise.
 */
int SetContains(Set s, int elem);

/**
 * Displays the elements of the set.
 *
 * @param s The set whose elements are to be displayed.
 */
void SetShow(Set s);

#endif