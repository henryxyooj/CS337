/*******************************************************************
* Author: Henry Xiong
*
* Description: header file to cipher.c file
* Citations:
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024

void addToArray(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH]);
void getString(char ciphChoice, char input[MAX_TEXT_LENGTH], int* isExit);
void encrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift);
void decrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift);
void display(char stringBuilder[MAX_TEXT_LENGTH], char ciphChoice, int isExit);


void throwInvalidShiftValueError(int shift, char* argv[]);
void throwInputMessageError(char input);
void throwSupportedOperationsError(int* isExit);