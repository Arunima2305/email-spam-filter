#ifndef SPAM_FILTER_H
#define SPAM_FILTER_H

#include "bloom_filter.h"
#include "trie.h"
#include "naive_bayes.h"

void setup_bloom_filter_and_trie();  
int classify_email(char *email_text);
int classify_email_with_features(char *email_text);

#endif
