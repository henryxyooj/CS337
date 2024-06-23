#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024

void getString(char ciphChoice, char input[MAX_TEXT_LENGTH], int* isExit);
void encrypt(char input[MAX_TEXT_LENGTH], int shift);

void throwInputMessageError(char input);
void throwSupportedOperationsError(int* isExit);