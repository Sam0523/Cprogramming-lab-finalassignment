#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"

BSTnode* insert(pBSTnode *ptr, const void* new_data)
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

		return ptr->node;
	}
	else if (ptr->cmp(ptr->node->data, new_data) > 0)
	{
		return insert(&ptr->node->lchild, new_data);
	}
	else if (ptr->cmp(ptr->node->data, new_data) < 0)
	{
		return insert(&ptr->node->rchild, new_data);
	}
	else
	{
		ptr->update(ptr->node->data);
		return ptr->node;
	}
}

void destroy(pBSTnode *ptr)
{
	if (ptr->node != NULL)
	{
		destroy(&ptr->node->lchild);
		destroy(&ptr->node->rchild);
		free(ptr->node->data);
		free(ptr->node);
		ptr->node = NULL;
	}
}

#ifdef DEBUG
void inorder_word(pBSTnode ptr)
{
	if (ptr.node == NULL)
		return;

	inorder_word(ptr.node->lchild);

	printf("%s\t%d\n", ((word*)ptr.node->data)->raw,
			((word*)ptr.node->data)->count);

	inorder_word(ptr.node->rchild);
}

void inorder_sen_bgn(pBSTnode ptr, int indent)
{
	if (ptr.node == NULL)
		return;

	inorder_sen_bgn(ptr.node->lchild, indent);

	printf("%*c%s\t%d\n",indent, ' ', ((sen_bgn_wrd*)ptr.node->data)->raw,
			((sen_bgn_wrd*)ptr.node->data)->count);
	inorder_sen_bgn(((sen_bgn_wrd*)ptr.node->data)->next_root,
			indent + strlen(((sen_bgn_wrd*)ptr.node->data)->raw));

	inorder_sen_bgn(ptr.node->rchild, indent);
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

	inorder_word(root);

	return 0;
}
#endif // TEST_BST
