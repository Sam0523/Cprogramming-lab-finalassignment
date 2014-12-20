#include <stdio.h>
#include <string.h>
#include "text_analysis.h"
#include "main.h"

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
				}
				else
				{
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
						0.4* N_w / N_s + 40.0 * N_c / N_w );
				}
			}
		}
	}

	return 0;
}
