#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024

void getString(char ciphChoice, char input[], int* isExit);
void throwInputMessageError(char input, char inputString[], int* isExit);