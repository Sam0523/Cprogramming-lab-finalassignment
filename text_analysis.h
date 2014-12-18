#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

// a data structure to store a word
typedef struct
{
	unsigned count;		// how many times the word appear
	unsigned char syllable;	// syllables count of the word
	char raw[0];		// the word
} word;

// node of a Binary Search Tree
typedef struct node
{
	word *data;		// pointer to a word
	struct node *lchild, *rchild;
} BSTnode;

#define ISHARD(wordptr) ((wordptr)->syllable > 2)
#define HARDEST_WORD_SUM 10
#define MOST_FREQUENT_WORD_SUM 10
#define BUF_SIZE_STEP 10

// read a word (seprated by space) from stream and return it
void analyse(FILE* stream);
word* fgetword(FILE* stream);
int count_syllables(char *word);

// the binary search tree to store words
extern BSTnode *root;

// the top hardest words
extern word* hardest[HARDEST_WORD_SUM];

// the most frequent hard words
extern word* frequent_hard[MOST_FREQUENT_WORD_SUM];

extern int N_x;		// number of syllables
extern int N_w;		// number of words
extern int N_s;		// number of sentences
extern int N_c;		// number of complex words
extern int N_u;		// number of unique words

#endif // TEXT_ANALYSIS_H
