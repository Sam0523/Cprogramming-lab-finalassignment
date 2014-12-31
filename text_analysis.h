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
#define HARDEST_WORDS 10
#define FREQENT_HARDS 10
#define DELIMITER " ,;:()[]{}<>\"\n\t@#$%^&*_-+="

// analyse text form stream
void analyse(FILE* stream);

// get a line from stream and return the string
// (memory space automatically allocated)
char* fgetline(FILE* stream);

// return the syllables of a word
int count_syllables(char *word);

// insert a word into the binary search tree,
// return newly inserted word or NULL
void insert(BSTnode** ptr, char* new_word);

// remove the whole binary search tree
void destory(BSTnode **ptr);

#ifdef DEBUG
// output the content of the BST, use for debug only
void inorder(BSTnode* ptr);
#endif // DEBUG

// the binary search tree to store words
extern BSTnode *root;

// the top hardest words
extern word* hardest[HARDEST_WORDS + 1];

// the most frequent hard words
extern word* frequent_hard[FREQENT_HARDS + 1];

extern int N_x;		// number of syllables
extern int N_w;		// number of words
extern int N_s;		// number of sentences
extern int N_c;		// number of complex words
extern int N_u;		// number of unique words

#endif // TEXT_ANALYSIS_H
