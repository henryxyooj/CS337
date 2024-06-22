#include "caesar.h"

int main(int argc, char *argv[]) {
    char input[MAX_TEXT_LENGTH];
    char ciphChoice = (argv[1])[1];
    //int shift = atoi(argv[2]);

    // throw any errors for incorrect input from user before asking for a string to decipher
    if (argc != 3) {
        // throw error for incorrect shift value
        if ((atoi(argv[2])) < 0 && ((atoi(argv[2]) > 25))) {
            puts("Invalid shift value");
        }
        // **throw error for encrypt/decrypt; note: turn back on shift on line 6**

        puts("Usage:\n\tTo encrypt: ./cipher -e <shift>\n\tTo decrypt: ./cipher -d <shift>");
        return 1;
    }

    // get a string from the user
    getString(ciphChoice, input);

    // switch case for either a encryption or decryption?
        // using ascii, add 2 to the ascii value?
        // not: keep the case letters; digits and special characters doesn't change
    return 0;
}