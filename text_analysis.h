#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

// name of this program in command line
extern char* program_name;

// analyse text form stream
void analyse(FILE* stream);

// get a line from stream and return the string
// (memory space automatically allocated)
char* fgetline(FILE* stream);

// plot image to filename.pnm
void plot_pnm(const char *filename);

// words count of beginning letters
extern int word_bgn_count[26];

// total words count
extern int word_total;

#endif // TEXT_ANALYSIS_H
