#ifndef MAIN_H
#define MAIN_H

// name of this program in command line
char* program_name;

// the binary search tree to store words
pBSTnode root = {
    .node	= NULL,
    .create	= word_create,
    .update	= word_update,
    .cmp	= word_str_cmp
};

// the top hardest words
word* hardest[HARDEST_WORDS + 1];

// the most frequent hard words
word* frequent_hard[FREQENT_HARDS + 1];

int N_x;	// number of syllables
int N_w;	// number of words
int N_s;	// number of sentences
int N_c;	// number of complex words
int N_u;	// number of unique words

// BST of first word of sentences beginning
pBSTnode sen_bgn_root = {
    .node	= NULL,
    .create	= sen_bgn_wrd_create,
    .update	= sen_bgn_wrd_update,
    .cmp	= sen_bgn_wrd_str_cmp
};

// array of words in sentences beginning
sen_bgn_wrd* common_begin[MAX_COMMON_BGN][MAX_COMMON_BGN] = {};

static void print_usage(void);

#endif // MAIN_H
