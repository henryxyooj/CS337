#include "text.h"

void grepLite(int argc, char *argv[]) {
    checkTerminalInputs(argc, argv);
}

void checkTerminalInputs(int argc, char *argv[]) {
    // Is the amount of arguments from terminal valid? At least is 3 and at most is 5.
    if (argc < 3 || argc > 5) {
        throwOutOfRangeArguments();
    }

    // Is the pattern a valid pattern?
    unsigned int index = 0;
    while (argv[index] != "\0") {
        index++;
    }

    if (index > MAX_PATTERN_CHARACTERS) {
        throwOutOfRangePattern();
    }

    // Were there any errors finding the file's name?  Does it include the .txt extension or is it NULL?
    const char *filename = argv[2];
    FILE *fptr = fopen(filename, "r");
    throwInvalidFileName(fptr, filename);



    // Are there any other optional flags used?

}

void throwInvalidFilename(FILE *fptr, const char *filename) {
    if (fptr == NULL) {
        printf("Failed to open %s\n", filename);
        exit(1);
    }
}

void throwInvalidPattern() {
    printf("Usage: ./main <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number\n");
    printf("Usage: <pattern> must be a single word you want to find within the desired file.\n");
    exit(1);
}

void throwInvalidFileName() {
    printf("Usage: ./main <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number\n");
    printf("Usage: <filename> must have the extension \".txt\" after the file's name.\n");
    exit(1);
}

void throwOutOfRangeArguments() {
    printf("Usage: ./main <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number\n");
    exit(1);
}

void throwOutOfRangePattern() {
    printf("Usage: Pattern can only be 10 characters long.\n");
    exit(1);
}

