#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"

int word_count_cmp(const void* pa, const void* pb)
{
	word *word1 = *(word**)pa, *word2 = *(word**)pb;
	if (word1 == NULL || word2 == NULL)
		return word2 - word1;
	else
		return word2->count - word1->count;
}

// update most freqent hard words, like bubble sort
static inline void update_freq_hard(word* new_word)
{
	qsort(frequent_hard, FREQENT_HARDS, sizeof(frequent_hard[0]),
			word_count_cmp);
	if (bsearch(&new_word, frequent_hard, FREQENT_HARDS,
				sizeof(frequent_hard[0]),
				word_count_cmp) != NULL)
		return;
	frequent_hard[FREQENT_HARDS] = new_word;
	for (word** ptr = frequent_hard + FREQENT_HARDS;
			ptr > frequent_hard && (ptr[-1] == NULL ||
				ptr[0]->count > ptr[-1]->count);
			ptr--)
	{
		word* tmp = *ptr;
		*ptr = ptr[-1];
		ptr[-1] = tmp;
	}
}

void word_add(pBSTnode *ptr, const void* new_data)
{
	char* new_word = (char*)new_data;

	// create new word
	word* new = (word*)malloc(sizeof(word) + strlen(new_word) + 1);
	new->count = 1;
	new->syllable = count_syllables(new_word);
	strcpy(new->raw, new_word);

	// create new node
	ptr->node = (BSTnode*)malloc(sizeof(BSTnode));
	ptr->node->data = new;
	ptr->node->lchild.node   = ptr->node->rchild.node   = NULL;
	ptr->node->lchild.add    = ptr->node->rchild.add    = ptr->add;
	ptr->node->lchild.update = ptr->node->rchild.update = ptr->update;
	ptr->node->lchild.cmp    = ptr->node->rchild.cmp    = ptr->cmp;

	// update counters
	N_u++;
	N_w++;
	N_c += ISHARD(new);
	N_x += new->syllable;

	// update hardest words, like bubble sort
	hardest[HARDEST_WORDS] = new;
	for (word** ptr = hardest + HARDEST_WORDS;
			ptr > hardest && (ptr[-1] == NULL ||
				ptr[0]->syllable > ptr[-1]->syllable);
			ptr--)
	{
		word* tmp = *ptr;
		*ptr = ptr[-1];
		ptr[-1] = tmp;
	}

	if (ISHARD(new))
	{
		update_freq_hard(new);
	}
}

void word_update(const BSTnode *ptr)
{
	word* word_data = (word*) ptr->data;

	// update old word
	word_data->count++;
	N_w++;
	N_c += ISHARD(word_data);
	N_x += word_data->syllable;

	if (ISHARD(word_data))
	{
		update_freq_hard(word_data);
	}
}

int word_str_cmp(const void* ptr, const void* data)
{
	return strcmp( ((word*)ptr)->raw, (char*)data);
}

