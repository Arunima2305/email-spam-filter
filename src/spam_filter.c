#include "spam_filter.h"
#include "bloom_filter.h"
#include "trie.h"
#include "naive_bayes.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SPAM_THRESHOLD 15// Set a threshold for spam word matches
#define MAX_WORD 10000    // Maximum words for hash-based frequency array

BloomFilter bloom_filter;
TrieNode *trie_root = NULL;

// List of common stop words
const char *stop_words[] = {"the", "is", "and", "of", "in", "a", "to"};
#define STOP_WORDS_COUNT (sizeof(stop_words) / sizeof(stop_words[0]))

// Check if a word is a stop word
int is_stop_word(const char *word) {
    for (int i = 0; i < STOP_WORDS_COUNT; i++) {
        if (strcmp(word, stop_words[i]) == 0) return 1;
    }
    return 0;
}

// Initializing the bloom filter and trie with spam words
void setup_bloom_filter_and_trie() {
    //printf("Initializing bloom filter and trie...\n");
    init_bloom_filter(&bloom_filter, 3);
    trie_root = create_trie_node();

    FILE *file = fopen("data/spam_words.txt", "r");
    if (file == NULL) {
        perror("Error opening spam_words.txt");
        exit(EXIT_FAILURE);
    }

    unsigned char bom[3];
    if (fread(bom, 1, 3, file) == 3) {
        if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)) {
            fseek(file, 0, SEEK_SET);  
        }
    }

    char word[50];
    while (fscanf(file, "%49s", word) != EOF) {
      //  printf("Adding word to bloom filter and trie: %s\n", word); 
        add_to_bloom_filter(&bloom_filter, word);
        insert_trie(trie_root, word);
    }
    fclose(file);
    //printf("Bloom filter and trie initialization completed.\n");
}

// Classify the email using bloom filter, trie, frequency matching, and Naive Bayes classifier
int classify_email_with_features(char *email_text) {
    //printf("Classifying email with advanced features...\n");

    Email email;
    memset(&email, 0, sizeof(email)); 

    int spam_word_count = 0;  
    char *word1 = NULL;       
    char *word = strtok(email_text, " ");
    while (word != NULL) {
        if (!is_stop_word(word)) {

            if (check_bloom_filter(&bloom_filter, word) && search_trie(trie_root, word)) {
            //    printf("Detected spam word in bloom filter and trie: %s\n", word);
                spam_word_count++;
            }

            int index = hash(word) % MAX_WORD;
            email.word_frequencies[index]++;

           
            if (word1) {
                char bigram[100];
                snprintf(bigram, sizeof(bigram), "%s %s", word1, word);
                int bigram_index = hash(bigram) % MAX_WORD;
                email.word_frequencies[bigram_index]++;
            }
            word1 = word; 
        }
        word = strtok(NULL, " ");
    }

   
    if (spam_word_count >= SPAM_THRESHOLD) {
    //    printf("Spam word count (%d) exceeded threshold (%d). Classified as SPAM.\n", spam_word_count, SPAM_THRESHOLD);
        return 1;  
    }

    // Using Naive Bayes score for final classification if threshold not reached
    int is_spam = calculate_naive_bayes_score(&email);
    //printf("Naive Bayes classification result: %s\n", is_spam ? "SPAM" : "HAM");

    return is_spam;
}
