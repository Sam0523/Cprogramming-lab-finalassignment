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
		char* new = strtok(buf, DELIMITER);

		while (new != NULL)
		{
			char *ptr, *next;

			for (ptr = new, next = new  + 1;
					*next != '\0';
					ptr++, next++)
			{
				*ptr = tolower(*ptr);

				// break into 2 (or more) words if more
				// than 2 hyphens appears in a row
				if (*ptr == '-' && *next == '-')
				{
					*ptr-- = '\0';
					// now ptr points to the last
					// character of new, i.e.
					// ptr == new + strlen(new) - 1

					// skip all hyphens in a row
					while (*next++ == '-');

					break;
				}
			}
			*ptr = tolower(*ptr);

			// deal with the end of sentence
			if (*ptr == '.' || *ptr == '?' || *ptr == '!')
			{
				N_s++;
				while (*ptr == '.' || *ptr == '?' || *ptr == '!')
					*ptr-- = '\0';
			}

			insert(&root, new);

			new = strtok(*next == '\0' ? NULL : next, DELIMITER);
		}
		free(buf);
	}
}
