#include "caesar.h"

int main(int argc, char *argv[]) {
    //char input[50];
    //char ciphChoice;
    int shift = atoi(argv[2]);

    // throw any errors for incorrect input from user before asking for a string to decipher
    if (argc != 2) {
        // throw error for incorrect shift value
        if (atoi(argv[2]) < 0) {
            puts("Invalid shift value");
        }
        // throw error for encrypt/decrypt
        if ((argv[1])[0] != '-' || ((argv[1])[1] != 'e') || ((argv[1])[1] != 'd')) {

        }
        throwUsageErrorMessage();
        return 1;
    }

    //ciphChoice = "hmm";

    printf("%s\t%d\t%s", argv[1], shift, argv[2]);

    // get a string from the user
    //getString(ciphChoice, input);

    // switch case for either a encryption or decryption?
        // using ascii, add 2 to the ascii value?
        // not: keep the case letters; digits and special characters doesn't change
    return 0;
}