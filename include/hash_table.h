#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 100

typedef struct HashNode {
    char *email;
    struct HashNode *next;
} HashNode;

void insert_hash_table(const char *email);
int search_hash_table(const char *email);

#endif
