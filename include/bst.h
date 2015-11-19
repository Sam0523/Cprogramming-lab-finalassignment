#ifndef BST_H
#define BST_H

typedef struct node BSTnode;
typedef struct pnode pBSTnode;

// pointer to a node of the BST
struct pnode
{
	BSTnode *node;

	// create new data field by raw data
	void* (*create)(const void* raw_data);

	// update old data field
	void (*update)(const void* data);

	// compare data field and raw data
	int (*cmp)(const void* data, const void* raw_data);
};

// node of a Binary Search Tree
struct node
{
	void *data;
	pBSTnode lchild, rchild;
};

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

#endif // BST_H
