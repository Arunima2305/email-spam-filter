#include "spam_filter.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "data/email_input.txt"  // Input file for individual email classification
#define BUFFER_SIZE 100000  // Buffer size for reading email text

//Function to calculate accuracy, precision, recall, and F1 score using the test dataset
void test_model_accuracy(Email *test_emails, int test_email_count) {
    int true_positives = 0, true_negatives = 0, false_positives = 0, false_negatives = 0;

    for (int i = 0; i < test_email_count; i++) {
        int is_spam = classify_email_with_features(test_emails[i].text);  // Predicted label
        int actual_label = test_emails[i].is_spam;  // Actual label from dataset

        if (is_spam == 1 && actual_label == 1) true_positives++;
        else if (is_spam == 0 && actual_label == 0) true_negatives++;
        else if (is_spam == 1 && actual_label == 0) false_positives++;
        
    }

 
    double accuracy = (double)(true_positives + true_negatives) / test_email_count;
    double precision = (double)true_positives / (true_positives + false_positives);

    printf("Model Performance:\n");
    printf("Accuracy: %.2f%%\n", accuracy * 100);
    printf("Precision: %.2f\n", precision);
\

}

// Main function to run the spam filter program
int main() {
    printf("Program started.\n");
    //printf("Setting up bloom filter and trie...\n");
    setup_bloom_filter_and_trie();
    //printf("Bloom filter and trie setup completed.\n");
    
    //Loading the training dataset (emails2.csv) for training the Naive Bayes classifier
    Email *training_emails = malloc(sizeof(Email) * MAX_EMAILS);
    if (training_emails == NULL) {
        fprintf(stderr, "Memory allocation for training emails failed.\n");
        exit(EXIT_FAILURE);
    }

    //printf("Loading training dataset (emails2.csv)...\n");
    int training_email_count = load_dataset("data/emails2.csv", training_emails,1);
    if (training_email_count == 0) {
        fprintf(stderr, "Error: No emails loaded from training dataset. Exiting program.\n");
        free(training_emails);
        exit(EXIT_FAILURE);
    }
    //printf("Training dataset loaded with %d emails.\n", training_email_count);

    //printf("Starting Naive Bayes training...\n");
    train_naive_bayes(training_emails, training_email_count);
    //display_naive_bayes_data();
    //printf("Naive Bayes training completed.\n");
    
    // Loading the test dataset (emails.csv) for evaluating model performance
    Email *test_emails = malloc(sizeof(Email) * MAX_EMAIL);
    if (test_emails == NULL) {
        fprintf(stderr, "Memory allocation for test emails failed.\n");
        free(training_emails);
        exit(EXIT_FAILURE);
    }

    //printf("Loading test dataset (emails.csv)...\n");
    int test_email_count = load_dataset("data/emails.csv", test_emails,0);
    if (test_email_count == 0) {
        fprintf(stderr, "Error: No emails loaded from test dataset. Exiting program.\n");
        free(training_emails);
        free(test_emails);
        exit(EXIT_FAILURE);
    }
    //printf("Test dataset loaded with %d emails.\n", test_email_count);

    //Evaluating model performance using the test dataset
    test_model_accuracy(test_emails, test_email_count);

    // Classifing a single email from input file (for individual testing)
    FILE *file = fopen(INPUT_FILE, "r");
    if (file == NULL) {
        perror("Error opening email input file");
        free(training_emails);
        free(test_emails);
        return 1;
    }

    // Read the email content into a buffer
    char email_text[BUFFER_SIZE];
    size_t read_size = fread(email_text, sizeof(char), BUFFER_SIZE - 1, file);
    fclose(file);
    email_text[read_size] = '\0';  // Null-terminate the buffer

    // Classifing the email
    int is_spam = classify_email_with_features(email_text);
    printf("The email is classified as: %s\n", is_spam ? "SPAM" : "HAM");

    // Free allocated memory
    free(training_emails);
    free(test_emails);

    return 0;
    
}
