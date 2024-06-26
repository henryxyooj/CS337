/*******************************************************************
* Author: Henry Xiong
*
* Description: driver file that shifts a certain number of places down or up the alphabet
* Citations:
*******************************************************************/

#include "caesar.h"

int main(int argc, char *argv[]) {
    char input[MAX_TEXT_LENGTH];
    char stringBuilder[MAX_TEXT_LENGTH] = "";
    char ciphChoice = (argv[1])[1];
    int isExit = 0;
    int shift = atoi(argv[2]);

    // throw any errors for incorrect input from user before asking for a string to decipher
    if (argc != 3) {
        if ((((strcmp(argv[0], "./cipher")) == 0) && ((strcmp(argv[1], "-e")) == 0)) ||
        (((strcmp(argv[0], "./cipher")) == 0) && ((strcmp(argv[1], "-d")) == 0)))  {
            return 1;
        }
        puts("Usage:\n\tTo encrypt: ./cipher -e <shift>\n\tTo decrypt: ./cipher -d <shift>");
        return 1;
    }

    // throws an error message if the choice isn't -e or -d
    if ((ciphChoice != 'e') && (ciphChoice != 'd')) {
        throwSupportedOperationsError(0);
        return 1;
    }

    // throws an error message if the choice isn't a number in between 0 and 25 inclusive
    if ((shift < 0) || (shift > 25)) {
        puts("Invalid shift value.\nUsage: <./cipher> <-d/-e> <0 <= 0 <= 25>");
        return 1;
    }

    // throws an error message if the choice are non integer values
    if (shift == 0) {
        throwInvalidShiftValueError(shift, argv);
    }

    while (!isExit) {
        // get a string from the user, if it's "exit", end the loop
        getString(ciphChoice, input, &isExit);
        if (isExit == 1) {
            break;
        }

        // switch case for either a encryption or decryption operation
        switch (ciphChoice) {
            case 'e':
                encrypt(input, stringBuilder, shift);
                break;
            case 'd':
                decrypt(input, stringBuilder, shift);
                break;
            default:
                throwSupportedOperationsError(&isExit);
        }
    }

    // display the results of the encrypted/decrypted messages
    display(stringBuilder, ciphChoice, isExit);

    return 0;
}