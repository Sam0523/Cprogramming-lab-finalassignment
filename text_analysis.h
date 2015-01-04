#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

typedef struct node BSTnode;
typedef struct pnode pBSTnode;

// pointer to a node of the BST
struct pnode
{
	void (*add)(pBSTnode*, const void*);
	void (*update)(const BSTnode*);
	int (*cmp)(const void*, const void*);
	BSTnode *node;
};

// node of a Binary Search Tree
struct node
{
	void *data;
	pBSTnode lchild, rchild;
};

// a data structure to store a word
typedef struct
{
	unsigned count;		// how many times this word appears
	unsigned char syllable;	// syllables count of the word
	char raw[0];		// the word
} word;

// three function to handle a BST of word
void word_add(pBSTnode *ptr, const void* new_data);
void word_update(const BSTnode *ptr);
int word_str_cmp(const void* ptr, const void* data);

#define ISHARD(wordptr) ((wordptr)->syllable > 2)
#define HARDEST_WORDS 10
#define FREQENT_HARDS 10
#define DELIMITER " ,;:()[]{}<>\"\n\t@#$%^&*_+="

// name of this program in command line
extern char* program_name;

// analyse text form stream
void analyse(FILE* stream);

// get a line from stream and return the string
// (memory space automatically allocated)
char* fgetline(FILE* stream);

// return the syllables of a word
int count_syllables(char *word);

// insert a word into the binary search tree,
// return newly inserted word or NULL
void insert(pBSTnode* ptr, const void* new_data);

// remove the whole binary search tree
void destory(pBSTnode *ptr);

#ifdef DEBUG
// output the content of the BST, use for debug only
void inorder(pBSTnode ptr);
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

#endif // TEXT_ANALYSIS_H
