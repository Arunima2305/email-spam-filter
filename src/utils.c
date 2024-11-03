#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Original hash function
unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * 31 + *str++;
    }
    return hash;
}
int ct=0;

//hash_with_seed function for bloom filter
unsigned int hash_with_seed(const char *str, int seed) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * seed + *str++;
    }
    return hash;
}

char email_texts[MAX_EMAIL][MAX_TEXT_LENGTH];

int load_dataset(const char *filename, Email *emails, int is_frequency_based) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[1000000];
    int email_count = 0;

   
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading header row\n");
        fclose(file);
        return 0;
    }

    while (fgets(line, sizeof(line), file) && email_count < MAX_EMAILS) {
        if (is_frequency_based) {
            // Frequency-based dataset processing
            int word_index = 0;
            char *token = strtok(line, ",");
            int col_count = 1;

            while (token != NULL) {
                int value = atoi(token);
                if (col_count <= 3001) {
                    emails[email_count].word_frequencies[word_index++] = value;
                } else if (col_count == 3002) {
                    emails[email_count].is_spam = value;
                }
                token = strtok(NULL, ",");
                col_count++;
            }

            while (word_index < MAX_WORDS) {
                emails[email_count].word_frequencies[word_index++] = 0;
            }
        } else {
            // Text-based dataset processing: process until last token for label
            char *text_token = strtok(line, ",");
            char *label_token = NULL;

            while (text_token != NULL) {
                label_token = strtok(NULL, ",");
                if (label_token == NULL) {
                    emails[email_count].is_spam = atoi(text_token);
                    break;
                }
                strncat(emails[email_count].text, text_token, MAX_TEXT_LENGTH - strlen(emails[email_count].text) - 1);
                strncat(emails[email_count].text, ",", MAX_TEXT_LENGTH - strlen(emails[email_count].text) - 1);
                text_token = label_token;
            }

           
            /*if(ct<10)
            {
                printf("Email %d - Text: %s\n", email_count + 1, emails[email_count].text);
                printf("Email %d - Spam/Ham Label: %d\n", email_count + 1, emails[email_count].is_spam);
                ct++;
            }*/
        }
        email_count++;
    }

    fclose(file);
    //printf("Total emails loaded: %d\n", email_count);
    return email_count;
}

// Loading word frequencies from an email text into an Email struct for Naive Bayes
void load_email_features(char *email_text, Email *email) {
    memset(email->word_frequencies, 0, sizeof(email->word_frequencies));

    char *ptr = strtok(email_text, " ");
    while (ptr != NULL) {
        int index = hash(ptr) % MAX_WORDS;
        email->word_frequencies[index]++;
       // printf("Word '%s' hashed to index %d\n", ptr, index);
        ptr = strtok(NULL, " ");
    }
}
