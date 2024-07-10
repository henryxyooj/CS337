/*******************************************************************
* Author: Henry Xiong

* Description:
* Contains all of the prototype functions, header files, and important
* final variables used for grep.c
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 1024
#define MAX_PATTERN_CHARACTERS 10

void grepLite(int argc, char *argv[]);

void checkTerminalInputs(int argc, char *argv[], int *isCaseInsensitive, int *isLineNumber, int *isWriteToFile);
void checkFile(FILE *fptr, const char *filename);
void checkFlag(int argc, char *argv[], int *isCaseInsensitive, int *isLineNumber, int *isWriteToFile);

void toLowerCase(char *str);

void messageNoPatternFound();
void messageToChoice(int isWriteToFile, char stringBuilder[], char *argv[], int isMatched);

void throwInvalidFlag();
void throwInvalidFilename(FILE *fptr, const char *filename);
void throwInvalidOutputFileName();
void throwInvalidPattern();
void throwInvalidFileName();
void throwOutOfRangeArguments();
void throwOutOfRangePattern();
