#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "hash_table.h"
#include "file_utils.h"

// Handle "wtf is <term>" command
void handle_is_command(HashTable *dictionary, char **args, int argc) {
    if (argc < 3) {
        printf("Error: No term provided. Use `wtf is <term>`.\n");
        return;
    }

    // Combine arguments to handle multi-word terms
    char term[256] = "";
    for (int i = 2; i < argc; i++) {
        strcat(term, args[i]);
        if (i < argc - 1) strcat(term, " "); // Add space between words
    }

    char *definition = hash_table_lookup(dictionary, term);
    if (definition) {
        printf("%s: %s\n", term, definition);
    } else {
        printf("Error: Term '%s' not found.\n", term);
    }
}

// Handle "wtf add <term>:<definition>" command
void handle_add_command(const char *filename, char *entry) {
    if (add_definition(filename, entry)) {
        printf("Definition added successfully.\n");
    } else {
        printf("Error: Could not add definition. Ensure the format is <term>:<definition>.\n");
    }
}
