
/*******************************************************************
* Author: Henry Xiong
*
* Description: source file for that contains the functions to the driver file to aid in ciphering
               user input
* Citations: https://stackoverflow.com/questions/8517032/shifting-chars-in-c, used for the shift
*            formula.  I was missing the mod 26 and the ending + 'a' value part.  I understand how
             the poster on stackoverflow got the formula though
*******************************************************************/

#include "caesar.h"

/*******************************************************************
* Description: Depending on which operation that the user inputted, this function
                will decide which proper display message will be used.
*******************************************************************/
void display(char stringBuilder[MAX_TEXT_LENGTH], char ciphChoice, int isExit) {
    switch (ciphChoice) {
        case 'e':
            printf("Encrypted text: %s\n", stringBuilder);
            break;
        case 'd':
            printf("Decrypted text: %s\n", stringBuilder);
            break;
        default:
            throwSupportedOperationsError(&isExit);
    }
}

/*******************************************************************
* Description: takes a destination array, stringBuilder, and appends the contents of the
                operated-on messages into the destination array
*******************************************************************/
void addToArray(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH]) {
    size_t len = strlen(input);

    // when entering a message, to save it, a "/n" is created at the end, change it to null
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // if there's already something in stringBuilder, append it
    if (strlen(stringBuilder) != 0) {
        strcat(stringBuilder, ", ");
    }

    // base case of no messages in the stringBuilder, then concatenate it with the current input
    strcat(stringBuilder, input);
}

/*******************************************************************
* Description: this function will use a formula to find out what the decrypted value will be
*******************************************************************/
void decrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift) {
    // loop through every char in the string
    //      find the ascii value of each char, and add the shift to it
    //      otherwise it's a special character, and ignore it
    for (unsigned long i = 0; i < strlen(input); i++) {
        // there's two if statements for the upper and lower case ASCII
        // you take input[i] - 'a' and then subtract it from shift because
        // input[i] - 'a' gives you the index, and then move it by the shift amount
        // you then mod it so that you can get it into the alphabet "bounds"
        // add 'a' to it at the end to get correct ASCII math value
        if ((input[i] >= 'a' && input[i] <= 'z')) {
            input[i] = ((input[i] - 'a') - shift) % 26 + 'a';
        } else if ((input[i] >= 'A' && input[i] <= 'Z')) {
            input[i] = ((input[i] - 'A') - shift) % 26 + 'A';
        }
    }

    addToArray(input, stringBuilder);
}

/*******************************************************************
* Description: this function will use a formula to find out what the encrypted value will be
*******************************************************************/
void encrypt(char input[MAX_TEXT_LENGTH], char stringBuilder[MAX_TEXT_LENGTH], int shift) {
    // loop through every char in the string
    //      find the ascii value of each char, and add the shift to it
    //      otherwise it's a special character, and ignore it
    for (unsigned long i = 0; i < strlen(input); i++) {
        if ((input[i] >= 'a' && input[i] <= 'z')) {
            input[i] = ((input[i] - 'a') + shift) % 26 + 'a';
        } else if ((input[i] >= 'A' && input[i] <= 'Z')) {
            input[i] = ((input[i] - 'A') + shift) % 26 + 'A';
        }
    }

    addToArray(input, stringBuilder);
}

/*******************************************************************
* Description: Takes the user input and decides if it should decrypt or encrypt
               If user puts in "exit", the boolean value will turn true to end the while loop
*******************************************************************/
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

/*******************************************************************
* Description: throws an error message if the user doesn't type any messages
                to get encoded/decoded.  Let's them know to enter a message
*******************************************************************/
void throwInputMessageError(char input) {
    if ((input == '\n') || (input == '\0')) {
        puts("Usage:\n<Enter message for requested operation>");
        exit(1);
    }
}

/*******************************************************************
* Description: throws an error message if user types into terminal a value besides -e or -d
                to let the user know that there's in error in deciding the ciphering options
*******************************************************************/
void throwSupportedOperationsError(int* isExit) {
    puts("Usage:\n <Supported operations are: \"-e\" or \"-d.\">");
    *isExit = 1;
    exit(1);
}