#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end_of_word;
} TrieNode;

TrieNode *create_trie_node();
void insert_trie(TrieNode *root, const char *word);
int search_trie(TrieNode *root, const char *word);

#endif
