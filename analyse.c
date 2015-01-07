#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "text_analysis.h"

// word delimiter
#define DELIMITER " .!?,;:()[]{}<>\"\n\t@#$%^&*_+="

void analyse(FILE* stream)
{
	// initialize
	word_total = 0;
	memset(word_bgn_count, 0, sizeof word_bgn_count);

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
			// change to lower case and deal with hyphens
			char *ptr, *next;
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

			word_total++;
			if (isalpha(*new))
				word_bgn_count[*new - 'a']++;

			new = *next == '\0' ? strtok(NULL, DELIMITER) : next;
		}

		free(buf);
	}

}
