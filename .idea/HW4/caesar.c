#include "caesar.h"



void getString(char ciphChoice, char input[], int* isExit) {
    switch (ciphChoice) {
        case 'e':
            printf("Enter a message to encode: ");
            fgets(input, MAX_TEXT_LENGTH, stdin);
            throwInputMessageError(input[0], input, isExit);
            break;
        case 'd':
            printf("Enter a message to decode: ");
            fgets(input, MAX_TEXT_LENGTH, stdin);
            throwInputMessageError(input[0], input, isExit);
            break;
        default:
            puts("Usage:\n <Supported operations are: \"-e\" or \"-d.\">");
            exit(1);
    }
}

void throwInputMessageError(char input, char inputString[], int* isExit) {
    if ((input == '\n') || (input == '\0')) {
        puts("Usage: Enter a message to encode: <Enter message for requested operation>");
        exit(1);
    }
    if ((inputString == "exit")) {
        puts("End program.");
        isExit = 1;
    }
}