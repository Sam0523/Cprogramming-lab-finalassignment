#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_analysis.h"
#include "main.h"

int main(int argc, char *argv[])
{
	program_name = argv[0];

	if (argc == 1)
	{
		fprintf(stderr, "%s: Error: missing input\n", program_name);
		print_usage();
		return EXIT_FAILURE;
	}

	while (++argv, --argc)
	{
		FILE *fp = fopen(*argv, "r");

		if (fp == NULL)
		{
			perror(*argv);
			continue;
		}

		printf("Analysing the file \"%s\"\n", *argv);

		analyse(fp);

		if (ferror(fp))
		{
			perror(*argv);
			continue;
		}

#ifdef DEBUG
		printf("word_total = %d\n", word_total);
		for (int i = 0; i < 26; i++)
			printf("word_bgn_count[%2d] = %d\n",
					i, word_bgn_count[i]);
#endif

		plot_pnm(*argv);
	}

	return EXIT_SUCCESS;
}

static void print_usage(void)
{
	printf("Usage: %s file1 [file2 ...]\n", program_name);
	printf("Plot a graph of word distributions in PNM format.\n");
}
