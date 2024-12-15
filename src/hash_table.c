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

// Lookup a single key (kept for backward compatibility)
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

// New function to lookup all definitions for a key
DefinitionList* hash_table_lookup_all(HashTable *table, const char *key) {
    DefinitionList *list = malloc(sizeof(DefinitionList));
    list->definitions = malloc(sizeof(char*) * 10);  // Initial capacity of 10
    list->count = 0;
    list->capacity = 10;

    unsigned int index = hash_function(key, table->size);
    HashNode *node = table->table[index];
    
    while (node) {
        if (strcmp(node->key, key) == 0) {
            // Resize if needed
            if (list->count >= list->capacity) {
                list->capacity *= 2;
                list->definitions = realloc(list->definitions, sizeof(char*) * list->capacity);
            }
            
            // Add the definition
            list->definitions[list->count] = strdup(node->value);
            list->count++;
        }
        node = node->next;
    }

    // If no definitions found, free and return NULL
    if (list->count == 0) {
        free(list->definitions);
        free(list);
        return NULL;
    }

    return list;
}

// Free the definition list
void free_definition_list(DefinitionList *list) {
    if (list) {
        for (int i = 0; i < list->count; i++) {
            free(list->definitions[i]);
        }
        free(list->definitions);
        free(list);
    }
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