#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"

void* sen_bgn_wrd_create(const void *new_data_raw)
{
	char* new_word = (char*)new_data_raw;

	// create new word
	sen_bgn_wrd* new =
		(sen_bgn_wrd*)malloc(sizeof(sen_bgn_wrd) + strlen(new_word) + 1);
	new->count = 1;
	new->next_root = (pBSTnode){NULL, sen_bgn_wrd_create, sen_bgn_wrd_update,
		sen_bgn_wrd_str_cmp};
	strcpy(new->raw, new_word);

	return new;
}

void sen_bgn_wrd_update(const void *data)
{
	sen_bgn_wrd *word_data = (sen_bgn_wrd*) data;

	word_data->count++;
}

int sen_bgn_wrd_str_cmp(const void *data, const void* str)
{
	return strcmp( ((sen_bgn_wrd*)data)->raw, (char*)str);
}

// programmer interface for insert a word of sencence beginning
void ins_sen_bgn(pBSTnode *ptr, const char *new_word)
{
	static pBSTnode *old;

	if (ptr == NULL)
		ptr = old;
	
	old = & ( (sen_bgn_wrd*) insert(ptr, new_word) -> data ) -> next_root;
}
