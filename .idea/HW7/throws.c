#include "file.h"

// argc has to be greater than 0 and less than 7
void throwOutOfBoundsTerminalInputs() {
    puts("Error: Invalid amount of arguments to the terminal.");
    puts("Usage: [./main] [grep] [directory] [pattern] [optional flag: -i or -n] [optional flag: -i or -n]");
    exit(1);
}

// if patterns are longer than 10 characters or no pattern entered
void throwOutOfBoundsPattern() {
    puts("Error: Max character for pattern has to be of length 10 or no pattern was entered.");
    puts("Usage: [./main] [grep] [directory] [pattern] [optional flag: -i or -n] [optional flag: -i or -n]");
    exit(1);

}

// if a directory doesn't exist, or format of the directory is wrong
void throwInvalidDirectory(char dir[BUFFER_SIZE]) {
    printf("The directory \"%s\" doesn't exist.\n", dir);
    puts("Usage: [./main] [grep] [directory] [pattern] [optional flag: -i or -n] [optional flag: -i or -n]");
    exit(1);

}

void throwInvalidFlagOption() {
    puts("Error: Flag(s) used aren't valid.");
    puts("Usage: [./main] [grep] [directory] [pattern] [optional flag: -i or -n] [optional flag: -i or -n]");
    puts("Usage: Case insensitive = [-i]\t Print line numbers = [-n]");
    exit(1);
}

void throwInvalidGrepCommand() {
    puts("Error: Grep wasn't used correctly.");
    puts("Usage: [./main] [grep] [directory] [pattern] [optional flag: -i or -n] [optional flag: -i or -n]");
    exit(1);
}