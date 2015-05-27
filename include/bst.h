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

#endif // BST_H
