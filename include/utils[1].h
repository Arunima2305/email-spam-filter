#ifndef UTILS_H
#define UTILS_H

#include "naive_bayes.h"

int load_dataset(const char *filename, Email *emails,int is_frequency_based);
void load_email_features(char *email_text, Email *email);
unsigned int hash(const char *str);             
unsigned int hash_with_seed(const char *str, int seed);  

#endif
