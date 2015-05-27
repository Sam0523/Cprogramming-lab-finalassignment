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
		sizeof(frequent_hard[0]), word_count_cmp) != NULL)
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

void* word_create(const void* new_data_raw)
{
    char* new_word = (char*)new_data_raw;

    // create new word
    word* new = (word*)malloc(sizeof(word) + strlen(new_word) + 1);
    new->count = 1;
    new->syllable = count_syllables(new_word);
    strcpy(new->raw, new_word);

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

    return new;
}

void word_update(const void *data)
{
    word* word_data = (word*) data;

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

int word_str_cmp(const void* data, const void* str)
{
    return strcmp( ((word*)data)->raw, (char*)str);
}

