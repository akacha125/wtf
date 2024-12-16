#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    
    // Create a lowercase version of the input key
    char *lower_key = strdup(key);
    for (int i = 0; lower_key[i]; i++) {
        lower_key[i] = tolower(lower_key[i]);
    }

    while (node) {
        // Create a lowercase version of the node's key
        char *lower_node_key = strdup(node->key);
        for (int i = 0; lower_node_key[i]; i++) {
            lower_node_key[i] = tolower(lower_node_key[i]);
        }

        if (strcmp(lower_node_key, lower_key) == 0) {
            free(lower_key);
            free(lower_node_key);
            return node->value;
        }

        free(lower_node_key);
        node = node->next;
    }

    free(lower_key);
    return NULL;
}

// Lookup all definitions for a key (case-insensitive)
DefinitionList* hash_table_lookup_all(HashTable *table, const char *key) {
    DefinitionList *list = malloc(sizeof(DefinitionList));
    list->definitions = malloc(sizeof(char*) * 10);  // Initial capacity of 10
    list->count = 0;
    list->capacity = 10;

    // Create a lowercase version of the input key for case-insensitive comparison
    char *lower_key = strdup(key);
    for (int i = 0; lower_key[i]; i++) {
        lower_key[i] = tolower(lower_key[i]);
    }

    for (int index = 0; index < table->size; index++) {
        // Directly iterate through the linked list at each index
        for (HashNode *current = table->table[index]; current != NULL; current = current->next) {
            // Create a lowercase version of the node's key
            char *lower_node_key = strdup(current->key);
            for (int i = 0; lower_node_key[i]; i++) {
                lower_node_key[i] = tolower(lower_node_key[i]);
            }

            // Compare lowercase versions
            if (strcmp(lower_node_key, lower_key) == 0) {
                // Resize if needed
                if (list->count >= list->capacity) {
                    list->capacity *= 2;
                    list->definitions = realloc(list->definitions, sizeof(char*) * list->capacity);
                }
                
                // Add the original definition (preserving original case)
                list->definitions[list->count] = strdup(current->value);
                list->count++;
            }

            free(lower_node_key);
        }
    }

    free(lower_key);

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