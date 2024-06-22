#include "caesar.h"

void getString(char ciphChoice, char input[]) {
    switch (ciphChoice) {
        case 'e':
            printf("Enter a a message to encode: ");
            fgets(input, MAX_TEXT_LENGTH, stdin);
            break;
        case 'd':
            printf("Enter a a message to decode: ");
            fgets(input, MAX_TEXT_LENGTH, stdin);
            break;
    }
}
