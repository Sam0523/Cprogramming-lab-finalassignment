#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "text_analysis.h"

// Width and max height of each bar, and intervals between bars, and edge of
// the whole image. Use multiples of CHAR_BIT for convenient.
#define BAR_WIDTH	32
#define BAR_HIGHT	192
#define INTERVAL	8
#define EDGE_WIDTH	16
#define PLOT_WIDTH	(EDGE_WIDTH*2 + BAR_WIDTH*26 + INTERVAL*25)
#define PLOT_HIGHT	(EDGE_WIDTH*2 + BAR_HIGHT)

void plot_pnm(const char* filename)
{
	FILE *fp;
	char outfilename[strlen(filename) + 4];

	strcpy(outfilename, filename);
	strcat(outfilename, ".pnm");

	if ((fp = fopen(outfilename, "wb")) == NULL)
	{
		perror(outfilename);
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "P4\n%d %d\n", PLOT_WIDTH, PLOT_HIGHT);

	for (int i = 0; i < EDGE_WIDTH; i++)
		for (int j = 0; j < PLOT_WIDTH/CHAR_BIT; j++)
			putc(0, fp);
	for (int i = BAR_HIGHT; i > 0; i--)
	{
		for (int j = 0; j < EDGE_WIDTH/CHAR_BIT; j++)
			putc(0, fp);
		for (int j = 0; j < 26; j++)
		{
			if (j != 0)
				for (int k = 0; k < INTERVAL/CHAR_BIT; k++)
					putc(0, fp);
			for (int k = 0; k < BAR_WIDTH/CHAR_BIT; k++)
				putc( i * word_total * 4 < word_bgn_count[j] * BAR_HIGHT * 26 ? UCHAR_MAX : 0, fp);
		}
		for (int j = 0; j < EDGE_WIDTH/CHAR_BIT; j++)
			putc(0, fp);
	}
	for (int i = 0; i < EDGE_WIDTH; i++)
		for (int j = 0; j < PLOT_WIDTH/CHAR_BIT; j++)
			putc(0, fp);

	fclose(fp);
	printf("Outputed to %s.\n", outfilename);
}
