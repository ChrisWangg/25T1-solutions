#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define INITIAL_NUM_SLOTS 11
#define MAX_LOAD_FACTOR 2.0


struct hashTable {
	struct node **slots;
	int numSlots;
	int numItems;
};

struct node {
	int key;
	int value;
	struct node *next;
};

static void freeList(struct node *list);
static struct node *doInsert(HashTable ht, struct node *list,
                             int key, int value);
static struct node *newNode(int key, int value);
static struct node *doDelete(HashTable ht, struct node *list, int key);
static inline unsigned int hash(int key, int N);

HashTable HashTableNew(void) {
	HashTable ht = malloc(sizeof(*ht));
	if (ht == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	ht->slots = calloc(INITIAL_NUM_SLOTS, sizeof(struct node *));
	ht->numSlots = INITIAL_NUM_SLOTS;
	ht->numItems = 0;

	return ht;
}

void HashTableFree(HashTable ht) {
	for (int i = 0; i < ht->numSlots; i++) {
		freeList(ht->slots[i]);
	}
	free(ht->slots);
	free(ht);
}

static void freeList(struct node *list) {
	struct node *curr = list;
	while (curr != NULL) {
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

void HashTableInsert(HashTable ht, int key, int value) {
	if (ht->numItems >= MAX_LOAD_FACTOR * ht->numSlots) {
		printf("warning: resize not implemented!\n");
	}

	int i = hash(key, ht->numSlots);
	ht->slots[i] = doInsert(ht, ht->slots[i], key, value);
}

static struct node *doInsert(HashTable ht, struct node *list,
                             int key, int value) {
	if (list == NULL) {
		ht->numItems++;
		return newNode(key, value);
	} else if (list->key == key) {
		list->value = value;
		return list;
	} else {
		list->next = doInsert(ht, list->next, key, value);
		return list;
	}
}

static struct node *newNode(int key, int value) {
	struct node *new = malloc(sizeof(struct node));
	if (new == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	new->key = key;
	new->value = value;
	new->next = NULL;
	return new;
}

void HashTableDelete(HashTable ht, int key) {
	int i = hash(key, ht->numSlots);
	ht->slots[i] = doDelete(ht, ht->slots[i], key);
}

static struct node *doDelete(HashTable ht, struct node *list, int key) {
	if (list == NULL) {
		return NULL;
	} else if (list->key == key) {
		ht->numItems--;
		struct node *newHead = list->next;
		free(list);
		return newHead;
	} else {
		list->next = doDelete(ht, list->next, key);
		return list;
	}
}

bool HashTableContains(HashTable ht, int key) {
	int i = hash(key, ht->numSlots);
	struct node *curr;
	for (curr = ht->slots[i]; curr != NULL; curr = curr->next) {
		if (curr->key == key) {
			return true;
		}
	}
	return false;
}

int HashTableGet(HashTable ht, int key) {
	int i = hash(key, ht->numSlots);
	struct node *curr;
	for (curr = ht->slots[i]; curr != NULL; curr = curr->next) {
		if (curr->key == key) {
			return curr->value;
		}
	}
	
	printf("error: key %d does not exist!\n", key);
	return -1;
}

int HashTableSize(HashTable ht) {
	return ht->numItems;
}

static inline unsigned int hash(int key, int N) {
	const unsigned int magic = 0x45d9f3b;
	unsigned int h = 1U + INT_MAX;
	h += key;
	h = ((h >> 16) ^ h) * magic;
	h = ((h >> 16) ^ h) * magic;
	h = (h >> 16) ^ h;
	return h % N;
}