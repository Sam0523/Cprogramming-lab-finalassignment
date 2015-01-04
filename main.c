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

		// initialize
		N_x = 0;
		N_w = 0;
		N_s = 0;
		N_c = 0;
		N_u = 0;

		destory(&root);
		memset(hardest, 0, sizeof(hardest));
		memset(frequent_hard, 0, sizeof(frequent_hard));

		analyse(fp);

		if (ferror(fp))
		{
			perror(*argv);
			continue;
		}

#ifdef DEBUG
		inorder(root);
		printf("N_x = %d\n", N_x);
		printf("N_w = %d\n", N_w);
		printf("N_s = %d\n", N_s);
		printf("N_c = %d\n", N_c);
		printf("N_u = %d\n", N_u);
#endif
		printf("Flesch Reading Ease Score:\n");
		printf("\tF = %lf\n",
				206.835 - 1.015 * N_w / N_s - 74.6 * N_x / N_w);

		printf("Gunning Fog Index:\n");
		printf("\tG = %lf\n",
				0.4 * N_w / N_s + 40.0 * N_c / N_w );

		printf("The top 10 'hardest' words:\n");
		for (int i = 0; hardest[i] != NULL; i++)
#ifdef DEBUG
			printf("\t%2d. %s\t%d\t%d\n", i + 1, hardest[i]->raw,
					hardest[i]->count, hardest[i]->syllable);
#else
			printf("\t%2d. %s\n", i + 1, hardest[i]->raw);
#endif

		printf("The top 10 most freqent 'hard words':\n");
		for (int i = 0; frequent_hard[i] != NULL; i++)
#ifdef DEBUG
			printf("\t%2d. %s\t%d\t%d\n", i + 1,
					frequent_hard[i]->raw,
					frequent_hard[i]->count,
					frequent_hard[i]->syllable);
#else
			printf("\t%2d. %s\n", i + 1, frequent_hard[i]->raw);
#endif

		printf("The total number of words:\n");
		printf("\t%d\n", N_w);

		printf("The total number of unique words:\n");
		printf("\t%d\n", N_u);
	}

	return EXIT_SUCCESS;
}

static void print_usage(void)
{
	printf("Usage: %s file1 [file2 ...]\n", program_name);
	printf("Analyse English text files.\n");
}
