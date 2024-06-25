#include "caesar.h"

void display(char stringBuilder[MAX_TEXT_LENGTH], char ciphChoice, int isExit) {
    switch (ciphChoice) {
        case 'e':
            printf("Encrypted text: %s\n", stringBuilder);
            break;
        case 'd':
            printf("Decrypted text: %s\n", stringBuilder);
            break;
        default:
            throwSupportedOperationsError(&isExit);
    }
}

void addToArray(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH]) {
    size_t len = strlen(input);

    // when entering a message, to save it, a /n is created at the end, change it to null
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // if there's already something in stringBuilder, append it
    if (strlen(stringBuilder) != 0) {
        strcat(stringBuilder, ", ");
    }

    // base case of no messages in the stringBuilder, then concatenate it with the current input
    strcat(stringBuilder, input);
}

void decrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift) {
    // loop through every char in the string
    //      find the ascii value of each char, and add the shift to it
    //      otherwise it's a special character, and ignore it
    for (unsigned long i = 0; i < strlen(input); i++) {
        if ((input[i] >= 'a' && input[i] <= 'z')) {
            input[i] = (input[i] - 'a' - shift) % 26 + 'a';
        } else if ((input[i] >= 'A' && input[i] <= 'Z')) {
            input[i] = (input[i] - 'A' - shift) % 26 + 'A';
        }
    }

    addToArray(input, stringBuilder);
}

void encrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift) {
    // loop through every char in the string
    //      find the ascii value of each char, and add the shift to it
    //      otherwise it's a special character, and ignore it
    for (unsigned long i = 0; i < strlen(input); i++) {
        if ((input[i] >= 'a' && input[i] <= 'z')) {
            input[i] = (input[i] - 'a' + shift) % 26 + 'a';
        } else if ((input[i] >= 'A' && input[i] <= 'Z')) {
            input[i] = (input[i] - 'A' + shift) % 26 + 'A';
        }
    }

    addToArray(input, stringBuilder);
}

void getString(char ciphChoice, char input[MAX_TEXT_LENGTH], int* isExit) {
    switch (ciphChoice) {
        case 'e':
            printf("Enter a message to encode: ");
            fgets(input, MAX_TEXT_LENGTH, stdin);
            throwInputMessageError(input[0]);
            break;
        case 'd':
            printf("Enter a message to decode: ");
            fgets(input, MAX_TEXT_LENGTH, stdin);
            throwInputMessageError(input[0]);
            break;
        default:
            throwSupportedOperationsError(isExit);
    }

    if (strcmp(input, "exit\n") == 0) {
        *isExit = 1;
        return;
    }
}

int findLength(char* str) {
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }

    return i;
}

void throwInputMessageError(char input) {
    if ((input == '\n') || (input == '\0')) {
        puts("Usage:\n<Enter message for requested operation>");
        exit(1);
    }
}

void throwSupportedOperationsError(int* isExit) {
    puts("Usage:\n <Supported operations are: \"-e\" or \"-d.\">");
    *isExit = 1;
    exit(1);
}