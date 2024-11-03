#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include <stdio.h>
// Hash table implementation
HashNode *table[TABLE_SIZE];

// Hash function to convert a string into an index
unsigned int hash_function(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash % TABLE_SIZE;
}

// Insert a new email into the hash table
void insert_hash_table(const char *email) {
    unsigned int index = hash_function(email);
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->email = strdup(email);
    new_node->next = table[index];
    table[index] = new_node;
}

// Search for an email in the hash table
int search_hash_table(const char *email) {
    unsigned int index = hash_function(email);
    HashNode *node = table[index];
    while (node) {
        if (strcmp(node->email, email) == 0) return 1;
        node = node->next;
    }
    return 0;
}
