#include <string.h>
#include "bloom_filter.h"
#include "utils.h" 

// Initialize the bloom filter with all zeros
void init_bloom_filter(BloomFilter *bf, int num_hashes) {
    memset(bf->bits, 0, BLOOM_SIZE);
    bf->num_hashes = num_hashes;
}

// Add a string to the bloom filter by setting the corresponding bits
void add_to_bloom_filter(BloomFilter *bf, const char *str) {
    for (int i = 0; i < bf->num_hashes; i++) {
        int index = hash_with_seed(str, 31 + i) % BLOOM_SIZE;  
        bf->bits[index] = 1;
    }
}

// Check if a string is in the bloom filter by checking all corresponding bits
int check_bloom_filter(BloomFilter *bf, const char *str) {
    for (int i = 0; i < bf->num_hashes; i++) {
        int index = hash_with_seed(str, 31 + i) % BLOOM_SIZE;  
        if (!bf->bits[index]) return 0;
    }
    return 1;
}
