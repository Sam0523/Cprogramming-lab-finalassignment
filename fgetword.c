#include <stdio.h>
#include <stdlib.h>
#include "text_analysis.h"

#define BUF_INIT_SIZE 100

word* fgetword(FILE* stream)
{
	size_t buf_size = BUF_INIT_SIZE;
	char* buf = (char*) malloc(buf_size);
	char ch;
	size_t len = 0;

	if (buf == NULL)
		// malloc failed
		return NULL;

	// skip spaces at the beginning
	while (isspace(ch = getc(stream)));
	ungetc(ch, stream);

	while ( (ch = getc(stream)) != EOF )
	{
		if (len == buf_size)
			// buffer is full, enlarge buffer
		{
			char* new_buf = realloc(buf, buf_size + BUF_INIT_SIZE);
			if (new_buf == NULL)
				// realloc failed
			{
				free(buf);
				return NULL;
			}
			else
				// succeed
			{
				buf = new_buf;
				buf_size += BUF_INIT_SIZE;
			}
		}

		if (ch == '-')
		{
		}
		else if (isblank(ch))
			// end of word, finish
		{
			ungetc(ch, stream);
			ch = '\0';
			break;
		}
		else if (isspace(ch))
			// end of a line

		buf[len++] = ch;
	}
	if (ch == EOF)
		buf[len++] = '\0';

	// free the extra memory
	char* result = realloc(buf, len);
	if (result == NULL)
		// realloc failed
	{
		free(buf);
		return NULL;
	}

	return result;
}

