#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "naive_bayes.h"

#define SMOOTHING_FACTOR 1.5 // Laplace smoothing factor
#define MIN_PROBABILITY 1e-10   // Minimum probability to avoid -INF logs

float spam_probabilities[MAX_WORDS];
float ham_probabilities[MAX_WORDS];
int total_spam_emails = 0;
int total_ham_emails = 0;
char vocabulary[MAX_WORDS][1000];  // Stores the vocabulary

void trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) {
        *str = '\0';
        return;
    }
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

void initialize_vocabulary(const char *first_row) {
    char row_copy[100000];
    strncpy(row_copy, first_row, sizeof(row_copy) - 1);
    row_copy[sizeof(row_copy) - 1] = '\0';

    char *token = strtok(row_copy, ",");
    int index = 0;

    while (token != NULL && index < MAX_WORDS) {
        trim_whitespace(token);
        if (strlen(token) > 0) {
            strncpy(vocabulary[index], token, sizeof(vocabulary[index]) - 1);
            vocabulary[index][sizeof(vocabulary[index]) - 1] = '\0';
            index++;
        }
        token = strtok(NULL, ",");
    }
}

void train_naive_bayes(Email *emails, int email_count) {
    int spam_word_count[MAX_WORDS];
    int ham_word_count[MAX_WORDS];
    int total_spam_word_count = MAX_WORDS * SMOOTHING_FACTOR;
    int total_ham_word_count = MAX_WORDS * SMOOTHING_FACTOR;

    for (int i = 0; i < MAX_WORDS; i++) {
        spam_word_count[i] = SMOOTHING_FACTOR;
        ham_word_count[i] = SMOOTHING_FACTOR;
    }

    for (int i = 0; i < email_count; i++) {
        if (emails[i].is_spam) {
            total_spam_emails++;
            for (int j = 0; j < MAX_WORDS; j++) {
                spam_word_count[j] += emails[i].word_frequencies[j];
                total_spam_word_count += emails[i].word_frequencies[j];
            }
        } else {
            total_ham_emails++;
            for (int j = 0; j < MAX_WORDS; j++) {
                ham_word_count[j] += emails[i].word_frequencies[j];
                total_ham_word_count += emails[i].word_frequencies[j];
            }
        }
    }

    for (int i = 0; i < MAX_WORDS; i++) {
        spam_probabilities[i] = fmaxf((float)spam_word_count[i] / total_spam_word_count, MIN_PROBABILITY);
        ham_probabilities[i] = fmaxf((float)ham_word_count[i] / total_ham_word_count, MIN_PROBABILITY);
    }
}

float calculate_naive_bayes_score(Email *email) {
    float spam_score = log(fmaxf((float)total_spam_emails / (total_spam_emails + total_ham_emails), MIN_PROBABILITY));
    float ham_score = log(fmaxf((float)total_ham_emails / (total_spam_emails + total_ham_emails), MIN_PROBABILITY));

    float unseen_word_probability_spam = fmaxf(1/ (total_spam_emails + 2 * MAX_WORDS * SMOOTHING_FACTOR), MIN_PROBABILITY);
    float unseen_word_probability_ham = fmaxf(1 / (total_ham_emails + 2 * MAX_WORDS * SMOOTHING_FACTOR), MIN_PROBABILITY);

    int total_words = 0;

    for (int i = 0; i < MAX_WORDS; i++) {
        if (email->word_frequencies[i] > 0) {
            total_words += email->word_frequencies[i];

            float spam_prob = spam_probabilities[i] > 0 ? spam_probabilities[i] : unseen_word_probability_spam;
            float ham_prob = ham_probabilities[i] > 0 ? ham_probabilities[i] : unseen_word_probability_ham;

            spam_score += email->word_frequencies[i] * log(fmaxf(spam_prob, MIN_PROBABILITY));
            ham_score += email->word_frequencies[i] * log(fmaxf(ham_prob, MIN_PROBABILITY));
        }
    }

    if (total_words > 0) {
        spam_score /= total_words;
        ham_score /= total_words;
    }

    //printf("Normalized Spam Score: %f, Normalized Ham Score: %f\n", spam_score, ham_score);

    if (spam_score > ham_score + 0.7 ){  // Adjust threshold as needed
        return 1;  // Classify as spam
    } else {
        return 0;  // Classify as ham
    }
}
