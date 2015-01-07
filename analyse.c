#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "text_analysis.h"

// word delimiter
#define DELIMITER " ,;:()[]{}<>/|\\\"\n\t@#$%^&*_+="

// speciall words and abbrs that need to be handled differently
static char* special_and_abbrs[] =
{
	"co.",
	"e.g.",
	"i.e.",
	"I",
	"Inc.",
	"Ltd.",
	"Mr.",
	"Mrs.",
	"Ms.",
	"No.",
	NULL
};

static char find_most_common_begin(pBSTnode ptr, int depth);

void analyse(FILE* stream)
{
	// initialize
	N_x = 0;
	N_w = 0;
	N_s = 0;
	N_c = 0;
	N_u = 0;

	destroy(&root);
	destroy_sen_bgn(&sen_bgn_root);
	memset(hardest, 0, sizeof(hardest));
	memset(frequent_hard, 0, sizeof(frequent_hard));
	memset(common_begin, 0, sizeof(common_begin));

	// input buffer
	char* buf;

	// sentence length
	int sen_len = 0;

	while ((buf = fgetline(stream)) != NULL)
	{
		// if this line ends with hyphen, join it with next line
		char* end = buf + strlen(buf);
		while (*--end == '-' && isalpha(end[-1]))
		{
			char *rest = fgetline(stream);

			if (rest == NULL)
				break;

			*end = '\0';
			buf = realloc(buf, strlen(buf) + strlen(rest) + 1);
			strcat(buf, rest);

			end = buf + strlen(buf);
		}

		// divide words
		char* new = strtok(buf, DELIMITER);
		while (new != NULL)
		{
			bool end_of_sentence = false;
			// next new word
			char *next = "";

			// skip some processes on special words and abbrs
			for (char** ptr = special_and_abbrs; *ptr!=NULL; ptr++)
			{
				if (strcmp(new, *ptr) == 0)
					goto insert;
			}

			// change to lower case and deal with hyphens
			char *ptr;
			for (ptr = new, next = new  + 1;
					*next != '\0';
					ptr++, next++)
			{
				*ptr = tolower(*ptr);

				// break into 2 (or more) words if the
				// hyphen isn't followed with a word
				if (*ptr == '-' && !isalnum(*next))
				{
					*ptr-- = '\0';
					// now ptr points to the last
					// character of new, i.e.
					// ptr == new + strlen(new) - 1

					// skip all hyphens in a row
					while (*++next == '-');

					break;
				}
			}
			*ptr = tolower(*ptr);

			// deal with the end of sentence
			if (*ptr == '.' || *ptr == '?' || *ptr == '!')
			{
				N_s++;
				end_of_sentence = true;
				while (*ptr == '.' || *ptr == '?' || *ptr == '!')
					*ptr-- = '\0';
			}

insert:
			insert(&root, new);

			if (sen_len < 5)
			{
				ins_sen_bgn(sen_len == 0 ? &sen_bgn_root : NULL,
						new);
				sen_len++;
			}

			if (end_of_sentence)
				sen_len = 0;

			new = *next == '\0' ? strtok(NULL, DELIMITER) : next;
		}

		free(buf);
	}

	hardest[HARDEST_WORDS] = NULL;
	frequent_hard[FREQENT_HARDS] = NULL;

	find_most_common_begin(sen_bgn_root, 0);

	for (int i = 1; i < MAX_COMMON_BGN && common_begin[i][i]; i++)
		common_begin[i][0]->raw[0] = toupper(common_begin[i][0]->raw[0]);
}

static char find_most_common_begin(pBSTnode ptr, int depth)
{
	if (ptr.node == NULL)
		return 0;

	char rval = 0;			// return value
	sen_bgn_wrd *word_data = (sen_bgn_wrd*)ptr.node->data;

	if (common_begin[depth][depth] == NULL ||
			word_data->count > common_begin[depth][depth]->count)
	{
		common_begin[depth][depth] = word_data;
		rval = 1 << depth;
	}

	rval |= find_most_common_begin(word_data->next_root, depth + 1);
	for (int i = depth; i < MAX_COMMON_BGN; i++)
	{
		if (rval & (1 << i))
			common_begin[i][depth] = word_data;
	}

	return rval | find_most_common_begin(ptr.node->lchild, depth) |
		find_most_common_begin(ptr.node->rchild, depth);
}
