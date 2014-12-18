#include <stdio.h>
#include "text_analysis.h"

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		fprintf(stderr, "Error: missing input\n");
		// TODO: output usage
	}
	else
	{
		while (++argv, --argc)
		{
			FILE *fp = fopen(*argv, "r");

			if (fp == NULL)
			{
				perror(*argv);
			}
			else
			{
				printf("Analysing the file \"%s\"\n", *argv);
				analyse(fp);
			}
		}
	}

	return 0;
}
