#include "caesar.h"

int main(int argc, char *argv[]) {
    char input[MAX_TEXT_LENGTH];
    char stringBuilder[MAX_TEXT_LENGTH];
    char ciphChoice = (argv[1])[1];
    int isExit = 0;
    int shift = atoi(argv[2]);

    // throw any errors for incorrect input from user before asking for a string to decipher
    if (argc != 3) {
        // throw error for incorrect shift value
        if ((atoi(argv[2])) < 0 && ((atoi(argv[2]) > 25))) {
            puts("Invalid shift value");
        }
        // **throw error for encrypt/decrypt

        puts("Usage:\n\tTo encrypt: ./cipher -e <shift>\n\tTo decrypt: ./cipher -d <shift>");
        return 1;
    }

    while (!isExit) {
        // get a string from the user
        getString(ciphChoice, input, &isExit);

        // switch case for either a encryption or decryption operation
        switch (ciphChoice) {
            case 'e':
                encrypt(input, stringBuilder, shift, ciphChoice);
                break;
            case 'd':
                decrypt(input, stringBuilder, shift, ciphChoice);
                break;
            default:
                throwSupportedOperationsError(&isExit);
        }

        // store the operated message into an array
    }

    // display the results of the encrypted/decrypted messages
    display(stringBuilder, ciphChoice, isExit);

    return 0;
}