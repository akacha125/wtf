#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Hash function
unsigned int hash_function(const char *key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % size;
}

// Create a hash table
HashTable* create_hash_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->table = calloc(size, sizeof(HashNode*));
    return table;
}

// Insert a key-value pair
void hash_table_insert(HashTable *table, const char *key, const char *value) {
    unsigned int index = hash_function(key, table->size);
    HashNode *new_node = malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = table->table[index];
    table->table[index] = new_node;
}

// Lookup a key
char* hash_table_lookup(HashTable *table, const char *key) {
    unsigned int index = hash_function(key, table->size);
    HashNode *node = table->table[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

// Free the hash table
void free_hash_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        HashNode *node = table->table[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->table);
    free(table);
}