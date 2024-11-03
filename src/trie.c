#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

// Define the number of characters in the English alphabet
TrieNode *create_trie_node() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) node->children[i] = NULL;
    return node;
}

// Insert a word into the trie
void insert_trie(TrieNode *root, const char *word) {
    TrieNode *node = root;
    while (*word) {
        if (isalpha((unsigned char)*word)) {  
            int index = tolower((unsigned char)*word) - 'a';
            if (index >= 0 && index < ALPHABET_SIZE) {  
                if (!node->children[index]) node->children[index] = create_trie_node();
                node = node->children[index];
            }
        }
        word++;
    }
    node->is_end_of_word = 1;
}

// Search for a word in the trie
int search_trie(TrieNode *root, const char *word) {
    if (!root || !word) return 0;  

    TrieNode *node = root;
    while (*word) {
        if (isalpha((unsigned char)*word)) {  
            int index = tolower((unsigned char)*word) - 'a';
            if (index < 0 || index >= ALPHABET_SIZE || !node->children[index]) return 0;
            node = node->children[index];
        }
        word++;
    }
    return node && node->is_end_of_word;
}
