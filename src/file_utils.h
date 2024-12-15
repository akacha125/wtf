#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "hash_table.h"

// Function prototypes
int load_definitions(const char *filename, HashTable *table);
int add_definition(const char *filename, const char *entry);

#endif