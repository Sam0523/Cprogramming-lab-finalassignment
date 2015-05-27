#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

#include "bst.h"

// a data structure to store a word
typedef struct
{
    unsigned count;		// how many times this word appears
    unsigned char syllable;	// syllables count of the word
    char raw[0];		// the word
} word;

// three function to handle a BST of word
void* word_create(const void* new_data_raw);
void word_update(const void *data);
int word_str_cmp(const void* data, const void* str);

// a word of the beginning of a sentence
typedef struct
{
    unsigned count;		// how many times this word appears
    pBSTnode next_root;	// tree of the next words
    char raw[0];		// this word
} sen_bgn_wrd;

// three function to handle the BST of sen_bgn_wrd
void* sen_bgn_wrd_create(const void *new_data_raw);
void sen_bgn_wrd_update(const void *data);
int sen_bgn_wrd_str_cmp(const void* data, const void* str);

// programmer interface for insert a word of sencence beginning
void ins_sen_bgn(pBSTnode *ptr, const char* new_word);
// programmer interface for destroy the whole sentence beginning
void destroy_sen_bgn(pBSTnode *ptr);

#define ISHARD(wordptr) ((wordptr)->syllable > 2)
#define HARDEST_WORDS 10
#define FREQENT_HARDS 10
#define MAX_COMMON_BGN 5

// name of this program in command line
extern char* program_name;

// analyse text form stream
void analyse(FILE* stream);

// get a line from stream and return the string
// (memory space automatically allocated)
char* fgetline(FILE* stream);

// return the syllables of a word
int count_syllables(char *word);

// insert new data into the binary search tree,
// return newly inserted node or NULL
BSTnode* insert(pBSTnode* ptr, const void* new_data_raw);

// remove the whole binary search tree
void destroy(pBSTnode *ptr);

#ifdef DEBUG
// output the word BST, use for debug only
void inorder_word(pBSTnode ptr);

// output the sentence beginning tree
void inorder_sen_bgn(pBSTnode ptr, int indent);

#endif // DEBUG

// the binary search tree to store words
extern pBSTnode root;

// the top hardest words
extern word* hardest[HARDEST_WORDS + 1];

// the most frequent hard words
extern word* frequent_hard[FREQENT_HARDS + 1];

extern int N_x;		// number of syllables
extern int N_w;		// number of words
extern int N_s;		// number of sentences
extern int N_c;		// number of complex words
extern int N_u;		// number of unique words

// BST of first word in sentences beginning
extern pBSTnode sen_bgn_root;

// array of words in sentences beginning
extern sen_bgn_wrd* common_begin[MAX_COMMON_BGN][MAX_COMMON_BGN];

#endif // TEXT_ANALYSIS_H
