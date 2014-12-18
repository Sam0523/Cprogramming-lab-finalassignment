#ifndef MAIN_H
#define MAIN_H

// the binary search tree to store words
BSTnode *root = NULL;

// the top hardest words
word* hardest[HARDEST_WORD_SUM] = {NULL};

// the most frequent hard words
word* frequent_hard[MOST_FREQUENT_WORD_SUM] = {NULL};

int N_x = 0;		// number of syllables
int N_w = 0;		// number of words
int N_s = 0;		// number of sentences
int N_c = 0;		// number of complex words
int N_u = 0;		// number of unique words

#endif // MAIN_H
