#ifndef COMMANDS_H
#define COMMANDS_H

#include "hash_table.h"

// Function prototypes
void handle_is_command(HashTable *dictionary, char **args, int argc);
void handle_add_command(const char *filename, char *entry);

#endif