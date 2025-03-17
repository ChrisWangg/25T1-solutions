/**
 * - Struct definitions should be in camelCase
 * - All helper functions, not called in any other file should be static
 * - Keep naming consistant, stick to camelCase for all helper functions and 
 *   variables.
 * - Is if head == NULL check even necessary in free list? (No)
 * - No need unnecessary return at end of void functions
 * - Print List function does not cover edge case of if list is empty
 * - Use better function names e.g. (add?, consider using appendList)
 * - All functions should have a header comment briefly describing what it does
 * - Don't include useless comments, or comments just everywhere
 * - Malloc does not need type casting
 * - Function order: Functions should be placed under where they are called
 * - Function prototypes in the same order in which they are in code
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

static struct node *appendList(struct node *list, int data);
static void printList(struct node *node);
static void freeList(struct node *head);


int main() {
	struct node *head = NULL;
	head = appendList(head, 1);
	head = appendList(head, 2);
	head = appendList(head, 3);
	head = appendList(head, 4);
	printList(head);
	freeList(head);
	return 0;
}

/** 
 * Function that creates a node and appends it to the end of a linked list
*/
static struct node *appendList(struct node *list, int data) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = NULL;
	if (list == NULL) {
		list = newNode;
	} else {
		struct node *lastNode = list;
		while (lastNode->next != NULL) {
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
	}
	return list;
}

/**
 * Function that prints a linked list
 */
static void printList(struct node *node) {
	while (node->next != NULL) {
		printf("%d -> ", node->data);
		node = node->next;
	}
	printf("%d\n", node->data);
}

/**
 * Function that free's memory of a linked list
 */
static void freeList(struct node *head) {
	if (head == NULL) {
		return;
	}
	struct node *temp = head;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}
