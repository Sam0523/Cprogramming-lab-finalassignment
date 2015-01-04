#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"

void insert(pBSTnode *ptr, const void* new_data)
{
	if (ptr->node == NULL)
	{
		// create new node
		ptr->node = (BSTnode*)malloc(sizeof(BSTnode));
		ptr->node->data = ptr->create(new_data);
		ptr->node->lchild.node   = ptr->node->rchild.node   = NULL;
		ptr->node->lchild.create = ptr->node->rchild.create = ptr->create;
		ptr->node->lchild.update = ptr->node->rchild.update = ptr->update;
		ptr->node->lchild.cmp    = ptr->node->rchild.cmp    = ptr->cmp;

	}
	else if (ptr->cmp(ptr->node->data, new_data) > 0)
	{
		insert(&ptr->node->lchild, new_data);
	}
	else if (ptr->cmp(ptr->node->data, new_data) < 0)
	{
		insert(&ptr->node->rchild, new_data);
	}
	else
	{
		ptr->update(ptr->node->data);
	}
}

void destory(pBSTnode *ptr)
{
	if (ptr->node != NULL)
	{
		destory(&ptr->node->lchild);
		destory(&ptr->node->rchild);
		free(ptr->node->data);
		free(ptr->node);
		ptr->node = NULL;
	}
}
/*
BSTnode *search(BSTnode *ptr, void* key)
{
	if (ptr == NULL)
		return NULL;
	else if (key < ptr->data)
		return search(ptr->lchild, key);
	else if (key > ptr->data)
		return search(ptr->rchild, key);
	else
		return ptr;
}

BSTnode* delete(BSTnode** ptr, void* key)
{
	if (*ptr == NULL)
		return NULL;

	else if (key < (*ptr)->data)
		(*ptr)->lchild = delete(&(*ptr)->lchild, key);
	else if (key > (*ptr)->data)
		(*ptr)->rchild = delete(&(*ptr)->rchild, key);
	else
		if ((*ptr)->lchild && (*ptr)->rchild)
		{
			BSTnode *prev = (*ptr)->lchild, *prev_father = (*ptr);
			BSTnode *next = (*ptr)->rchild, *next_father = (*ptr);
		
			while (prev->rchild)
				prev_father = prev, prev = prev->rchild;
			while (next->lchild)
				next_father = next, next = next->lchild;
			if ( 2 * (*ptr)->data < prev->data + next->data )
			{
				(*ptr)->data = prev->data;
				prev_father->rchild = prev->lchild;
				free(prev);
			}
			else
			{
				(*ptr)->data = next->data;
				next_father->lchild = next->rchild;
				free(next);
			}
		}
		else
		{
			BSTnode* tmp = (BSTnode*)( (int)(*ptr)->lchild | (int)(*ptr)->rchild );
			free((*ptr));
			return tmp;
		}

	return *ptr;
}
*/

#ifdef DEBUG
void inorder(pBSTnode ptr)
{
	if (ptr.node == NULL)
		return;

	inorder(ptr.node->lchild);

	printf("%s\t%d\n", ((word*)ptr.node->data)->raw,
			((word*)ptr.node->data)->count);

	inorder(ptr.node->rchild);
}
#endif // DEBUG

#ifdef TEST_BST
#define TEST_SIZE 10
#include "main.h"

int main(void)
{
	char word[TEST_SIZE];

	while (printf("Input a word:\n"), scanf("%s", word) == 1)
		insert(&root, word);

	inorder(root);

	return 0;
}
#endif // TEST_BST
