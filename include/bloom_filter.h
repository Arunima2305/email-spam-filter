#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#define BLOOM_SIZE 1000

typedef struct {
    unsigned char bits[BLOOM_SIZE];
    int num_hashes;
} BloomFilter;

void init_bloom_filter(BloomFilter *bf, int num_hashes);
void add_to_bloom_filter(BloomFilter *bf, const char *str);
int check_bloom_filter(BloomFilter *bf, const char *str);

#endif
