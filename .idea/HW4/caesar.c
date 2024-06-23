#include "caesar.h"

void encrypt(char input[MAX_TEXT_LENGTH], int shift) {
    // find the size of input

    // loop through every char in the string
    //      find the ascii value of each char, and add the shift to it
    //      otherwise it's a special character, and ignore it

    // add
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

void throwInputMessageError(char input) {
    if ((input == '\n') || (input == '\0')) {
        puts("Usage: Enter a message to encode: <Enter message for requested operation>");
        exit(1);
    }
}

void throwSupportedOperationsError(int* isExit) {
    puts("Usage:\n <Supported operations are: \"-e\" or \"-d.\">");
    *isExit = 1;
    exit(1);
}