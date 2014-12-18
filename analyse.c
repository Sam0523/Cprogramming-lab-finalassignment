#include <stdio.h>
#include <ctype.h>
#include "text_analysis.h"

void analyse(FILE* stream)
{
	// current state in the text
	enum
	{
		OUT_OF_SENTENCE,
		END_OF_SENTENCE_UNSURE,	// meet '.', '!' or '?'
		OUT_OF_WORD,		// out of words, in a sentence
		END_OF_WORD_UNSURE,	// meet '-' in word
		IN_WORD,		// in a word, in a sentence
	} current_state = OUT_OF_SENTENCE;

	// pointer to a inputing word, and buffer size of word.raw
	word* new_word = NULL;
	size_t buf_size = 0;

	// small buffer
	char ch;

	// pointer to the end of inputing word
	char* wordptr = NULL;

	while ((ch = getc(stream)) != EOF)
	{
		if (wordptr - new_word.raw == buf_size)
			// buffer is full, enlarge buffer
		{
			word* new_buf = (word*) realloc(new_word,
					sizeof(word) + buf_size + BUF_SIZE_STEP);

			if (new_buf == NULL)
				// realloc failed
			{
				perror("text-analyse");
				free(new_word);
				exit(1);
			}
			else
				// succeed
			{
				buf_size += BUF_SIZE_STEP;
				wordptr = new_buf.raw + (wordptr - new_word.raw);
				new_word = new_buf;
			}
		}

		if (isalnum(ch))
		{
			current_state = IN_WORD;
			*ptr++ = tolower(ch);
		}
		else switch(ch)
		{
			case '.': case '!': case '?':
				if (current_state >= OUT_OF_WORD)
					current_state = END_OF_SENTENCE_UNSURE;
				break;
			case '-':
				if (current_state == IN_WORD)
					current_state = END_OF_WORD_UNSURE;
				else if (current_state == END_OF_WORD_UNSURE)
					current_state = OUT_OF_WORD;
				break;
			case '\"': case ']': case ')': case '>':
				if (current_state == END_OF_SENTENCE_UNSURE)
					// end of sentence
					; // TODO
				break;
			case '\n':
				if (current_state == IN_WORD)
					// end of word
					; // TODO
			case ' ': case '\t':
				if (current_state >= END_OF_WORD_UNSURE)
					// end of word
					; // TODO
				break;
		}

		if (current_state > OUT_OF_WORD)
			// end of word
			; // TODO

