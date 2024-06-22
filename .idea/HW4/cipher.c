#include "caesar.h"

int main(int argc, char *argv[]) {
    //char input[50];
    //char ciphChoice;
    int shift;

    // check for encryption or decryption, use lab1 to type in "-e" or "-d" with the argc and argv?
    // throw more errors later
    if (argc != 2 || argc == 1 || argc == 0) {
        if (atoi(argv[2]) < 0) {
            puts("Invalid shift value");
        }
        throwUsageErrorMessage();
        return 1;
    }

    //ciphChoice = "hmm";
    shift = atoi(argv[2]);

    printf("%s\t%d\t%s", argv[1], shift, argv[2]);

    // get a string from the user
    //getString(ciphChoice, input);

    // switch case for either a encryption or decryption?
        // using ascii, add 2 to the ascii value?
        // not: keep the case letters; digits and special characters doesn't change
    return 0;
}