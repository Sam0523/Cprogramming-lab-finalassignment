#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "text_analysis.h"
#include "main.h"

int main(int argc, char *argv[])
{
	program_name = basename(argv[0]);

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
		inorder_word(root);
		printf("---------------\n");
		inorder_sen_bgn(sen_bgn_root, 0);
		printf("N_x = %d\n", N_x);
		printf("N_w = %d\n", N_w);
		printf("N_s = %d\n", N_s);
		printf("N_c = %d\n", N_c);
		printf("N_u = %d\n", N_u);
#endif
		printf("Flesch Reading Ease Score:\n");
		printf("\tF = %lf\n", 206.835 - 1.015 * N_w / N_s - 74.6 * N_x / N_w);

		printf("Gunning Fog Index:\n");
		printf("\tG = %lf\n", 0.4 * N_w / N_s + 40.0 * N_c / N_w );

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

		printf("The most frequent sentence beginnings are:\n");
		for (int i = 1; i < MAX_COMMON_BGN && common_begin[i][i] != NULL; i++)
		{
#ifdef DEBUG
			printf("[%d words, used %d times]: \"", i + 1,
					common_begin[i][i]->count);
#else
			printf("[%d words, used in %.2f%% of sentences]: \"",
					i + 1, 100. * common_begin[i][i]->count / N_s);
#endif
			for (int j = 0; j <= i; j++)
				printf(j == 0 ? "%s" : " %s", common_begin[i][j]->raw);
			printf("\"\n");
		}
	}

	return EXIT_SUCCESS;
}

static void print_usage(void)
{
	printf("Usage: %s <file> [file ...]\n", program_name);
	printf("Analyse English text files.\n");
}
