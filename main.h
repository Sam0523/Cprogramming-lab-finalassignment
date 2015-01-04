#ifndef MAIN_H
#define MAIN_H

// name of this program in command line
char* program_name;

// the binary search tree to store words
pBSTnode root = {word_add, word_update, word_str_cmp, NULL};

// the top hardest words
word* hardest[HARDEST_WORDS + 1];

// the most frequent hard words
word* frequent_hard[FREQENT_HARDS + 1];

int N_x;		// number of syllables
int N_w;		// number of words
int N_s;		// number of sentences
int N_c;		// number of complex words
int N_u;		// number of unique words

static void print_usage(void);

#endif // MAIN_H
