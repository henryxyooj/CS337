#include "caesar.h"

void display(char stringBuilder[MAX_TEXT_LENGTH]) {
    printf("%s", stringBuilder);
}


void addToArray(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH]) {
    char comma[2] = ", ";
    int length = findLength(stringBuilder);

    // base case of an empty stringbuilder
    if (length == 0) {
        strcat(stringBuilder, input);
    }
    else {
        strcat(stringBuilder, comma);
        strcat(stringBuilder, input);
    }
}

void encrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift) {
    // loop through every char in the string
    //      find the ascii value of each char, and add the shift to it
    //      otherwise it's a special character, and ignore it
    for (unsigned long i = 0; i < (strlen(input) - 1); i++) {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
            input[i] = input[i] + shift;
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