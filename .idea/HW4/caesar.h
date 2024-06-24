#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024

void getString(char ciphChoice, char input[MAX_TEXT_LENGTH], int* isExit);
void encrypt(char input[MAX_TEXT_LENGTH], int shift);
void display(char input[MAX_TEXT_LENGTH]);
void addToArray(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH]);

int findLength(char* str);

void throwInputMessageError(char input);
void throwSupportedOperationsError(int* isExit);