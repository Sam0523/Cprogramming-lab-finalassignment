#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_INIT_SIZE 10

char* fgetline(FILE* stream)
{
    size_t buf_size = BUF_INIT_SIZE;
    char* buf = (char*) malloc(buf_size * sizeof(char));
    size_t len;
    char *rval = NULL;

    if (buf == NULL || feof(stream))
	// malloc failed or end of file
	return NULL;

    if (fgets(buf, buf_size, stream) != NULL)
    {
	len = strlen(buf);

	while (buf[len - 1] != '\n' && !feof(stream))
	{
	    // input isn't finish
	    buf_size *= 2;

	    buf = realloc(buf, buf_size * sizeof(char));

	    if (fgets(buf + len, buf_size/2 + 1, stream) == NULL)
		break;

	    len = strlen(buf);
	}
	if (buf[len - 1] == '\n')
	    buf[len - 1] = '\0';

	// free the extra memory
	rval = realloc(buf, len);
    }
    if (ferror(stream))
    {
	//perror(NULL);
	free(buf);
	return NULL;
    }

    return rval;
}
