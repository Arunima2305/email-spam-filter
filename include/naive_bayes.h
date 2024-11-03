#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#define MAX_EMAILS 5172
#define MAX_EMAIL 5731
#define MAX_WORDS 100000
#define MAX_TEXT_LENGTH 100000

typedef struct {
    int word_frequencies[MAX_WORDS];
    int is_spam;
    char text[MAX_TEXT_LENGTH];
} Email;

extern float spam_probabilities[MAX_WORDS];
extern float ham_probabilities[MAX_WORDS];
extern int total_spam_emails;
extern int total_ham_emails;

void train_naive_bayes();
float calculate_naive_bayes_score(Email *email);
void save_probabilities(const char *filename);
void load_probabilities(const char *filename);
void display_naive_bayes_data();
void initialize_vocabulary(const char *first_row);


#endif
