#include <stdbool.h>
typedef struct hashTable *HashTable;

/**
 * Creates a new empty hash table
 */
HashTable HashTableNew(void);

/**
 * Frees all memory allocated to the hash table
 */
void HashTableFree(HashTable ht);

/**
 * Inserts a key-value pair into the hash table. If the key already
 * exists, the existing value is replaced with the given value.
 */
void HashTableInsert(HashTable ht, int key, int value);

/**
 * Deletes a key-value pair from the hash table, if it exists
 */
void HashTableDelete(HashTable ht, int key);

/**
 * Returns true if the hash table contains the given key, and false
 * otherwise
 */
bool HashTableContains(HashTable ht, int key);

/**
 * Returns the value associated with the given key in the hash table.
 * Assumes that the key exists.
 */
int HashTableGet(HashTable ht, int key);

/**
 * Returns the number of key-value pairs in the hash table
 */
int HashTableSize(HashTable ht);