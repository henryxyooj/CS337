#include "caesar.h"

/*
void getString(char ciphChoice, char* input[]) {
    switch (ciphChoice) {
        case "-e":
            break;
        case "-d":
            break;
    }
*/

void throwUsageErrorMessage() {
    puts("Usage:\n\tTo encrypt: ./cipher -e <shift>\n\tTo decrypt: ./cipher -d <shift>");
}