#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 1024
#define MAX_PATTERN_CHARACTERS 10

void grepLite(int argc, char *argv[]);

void checkTerminalInputs(int argc, char *argv[], int *isCaseInsensitive, int *isLineNumber);
void checkFile(FILE *fptr, const char *filename);

void messageNoPatternFound();
void displayResults(char stringBuilder[MAX_CHARACTERS], char lineBuilder[MAX_CHARACTERS]);

void throwInvalidFlag();
void throwInvalidFilename(FILE *fptr, const char *filename);
void throwInvalidPattern();
void throwInvalidFileName();
void throwOutOfRangeArguments();
void throwOutOfRangePattern();