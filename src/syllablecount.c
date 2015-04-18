#include <stdio.h>
#include <string.h>
#define false 0
#define true 1

int count_syllables(char *word)
{
	char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y'};
	int lastWasVowel = false, foundVowel = false;
	int numVowels = 0;
	int i,j;
	char c,v;
	int len = strlen(word);

	for(i=0;i<len;i++) /*loop through each character in the word*/
	{
		c=word[i];
		foundVowel = false;
		for(j=0;j<6;j++) /*run through the vowels*/
		{
		v=vowels[j];
		if ((v == c) && lastWasVowel) /*ignore dipthongs (double vowels)*/
		{
			foundVowel = true;
			lastWasVowel = true;
			break;
		}
		else if ((v == c) && !lastWasVowel)
		{
			numVowels++;
			foundVowel = true;
			lastWasVowel = true;
			break;
		}
		}
		if (!foundVowel) /*no vowel found*/
		lastWasVowel = false;
	}

	/* remove es at the end of the word, because it's often silent*/
	if ((numVowels>1) && (len > 2) && strcmp(&word[len-2],"es")==0)
		numVowels--;
	/* remove a silent e at the end of a word*/
	else if ((numVowels>1) && (len > 1) && word[len-1]=='e')
		numVowels--;

	return numVowels;
}

#ifdef TEST_SYLLABLECOUNT
int main(int argc, char *argv[])
{
	if (argc<2)
		printf("Insufficient command line args\n");
	else	
		printf("\nWe got %d syllables from [%s]\n",count_syllables(argv[1]),argv[1]);
}
#endif // TEST_SYLLABLECOUNT

