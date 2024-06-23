#include "caesar.h"

void encrypt(char input[MAX_TEXT_LENGTH]) {

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
            puts("Usage:\n <Supported operations are: \"-e\" or \"-d.\">");
            *isExit = 1;
            exit(1);
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