#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"

void insert(BSTnode** ptr, word* data)
{
	if (*ptr == NULL)
	{
		*ptr = (BSTnode*)malloc(sizeof(BSTnode));
		(*ptr)->data = data;
		(*ptr)->lchild = NULL;
		(*ptr)->rchild = NULL;
	}
	else if (strcmp(data->raw, (*ptr)->data->raw) > 0)
	{
		insert(&(*ptr)->rchild, data);
	}
	else if (strcmp(data->raw, (*ptr)->data->raw) < 0)
	{
		insert(&(*ptr)->lchild, data);
	}
	else
	{
		(*ptr)->data->count++;
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

void inorder(BSTnode* ptr)
{
	if (ptr->lchild != NULL)
		inorder(ptr->lchild);

	printf("%d\n", ptr->data);

	if (ptr->rchild != NULL)
		inorder(ptr->rchild);
}
*/
