#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Hash node structure
typedef struct HashNode {
    char *key;
    char *value;
    struct HashNode *next;
} HashNode;

// Hash table structure
typedef struct HashTable {
    int size;
    HashNode **table;
} HashTable;

// Function prototypes
HashTable* create_hash_table(int size);
void hash_table_insert(HashTable *table, const char *key, const char *value);
char* hash_table_lookup(HashTable *table, const char *key);
void free_hash_table(HashTable *table);

#endif