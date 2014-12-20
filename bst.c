#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"

void insert(BSTnode** ptr, char* new_word)
{
	if (*ptr == NULL)
	{
		word* new = (word*)malloc(sizeof(word) + strlen(new_word) + 1);
		new->count = 1;
		new->syllable = count_syllables(new_word);
		strcpy(new->raw, new_word);

		*ptr = (BSTnode*)malloc(sizeof(BSTnode));
		(*ptr)->data = new;
		(*ptr)->lchild = NULL;
		(*ptr)->rchild = NULL;

		N_u++;
		N_w++;
		N_c += ISHARD(new);
		N_x += new->syllable;
	}
	else if (strcmp(new_word, (*ptr)->data->raw) > 0)
	{
		insert(&(*ptr)->rchild, new_word);
	}
	else if (strcmp(new_word, (*ptr)->data->raw) < 0)
	{
		insert(&(*ptr)->lchild, new_word);
	}
	else
	{
		(*ptr)->data->count++;
		N_w++;
		N_c += ISHARD((*ptr)->data);
		N_x += (*ptr)->data->syllable;
	}
}

void destory(BSTnode **ptr)
{
	if (*ptr != NULL)
	{
		destory(&(*ptr)->lchild);
		destory(&(*ptr)->rchild);
		free(*ptr);
		*ptr = NULL;
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
void inorder(BSTnode* ptr)
{
	if (ptr->lchild != NULL)
		inorder(ptr->lchild);

	puts(ptr->data->raw);

	if (ptr->rchild != NULL)
		inorder(ptr->rchild);
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
