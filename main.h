#ifndef MAIN_H
#define MAIN_H

// the binary search tree to store words
BSTnode *root;

// the top hardest words
word* hardest[HARDEST_WORD_SUM];

// the most frequent hard words
word* frequent_hard[MOST_FREQUENT_WORD_SUM];

int N_x;		// number of syllables
int N_w;		// number of words
int N_s;		// number of sentences
int N_c;		// number of complex words
int N_u;		// number of unique words

#endif // MAIN_H
