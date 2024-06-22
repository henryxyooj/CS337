#include "caesar.h"

void getString(char ciphChoice, char input[]) {
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
            puts("Usage: <Supported operations are: \"-e\" or \"-d.\">");
            exit(1);
    }
}

void throwInputMessageError(char input) {
    if ((input == '\n') || (input == '\0')) {
        puts("Usage: Enter a message to encode: <Enter message for requested operation>");
    }
}