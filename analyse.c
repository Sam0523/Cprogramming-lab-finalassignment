#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "text_analysis.h"

void analyse(FILE* stream)
{
	// input buffer
	char* buf;

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
			char *ptr;

			// change whole word to lower case
			for (ptr = new; *ptr != '\0'; ptr++)
				*ptr = tolower(*ptr);
			ptr--;

			// deal with the end of sentence
			if (*ptr == '.' || *ptr == '?' || *ptr == '!')
			{
				N_s++;
				while (*ptr == '.' || *ptr == '?' || *ptr == '!')
					*ptr-- = '\0';
			}

			insert(&root, new);

			new = strtok(NULL, DELIMITER);
		}

		free(buf);
	}
}
