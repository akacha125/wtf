#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "hash_table.h"

// Load definitions from file into hash table
int load_definitions(const char *filename, HashTable *table) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *term = strtok(line, ":");
        char *definition = strtok(NULL, "\n");
        if (term && definition) {
            hash_table_insert(table, term, definition);
        }
    }

    fclose(file);
    return 1;
}

// Add a new definition to the file
int add_definition(const char *filename, const char *entry) {
    FILE *file = fopen(filename, "a");
    if (!file) return 0;

    fprintf(file, "%s\n", entry);
    fclose(file);
    return 1;
}