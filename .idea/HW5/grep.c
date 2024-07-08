#include "text.h"

void grepLite(int argc, char *argv[]) {
    int isCaseInsensitive = 0;
    int isLineNumber = 0;

    checkTerminalInputs(argc, argv, isCaseInsensitive, isLineNumber);
}

void checkTerminalInputs(int argc, char *argv[], int *isCaseInsensitive, int *isLineNumber) {
    // Is the amount of arguments from terminal valid? At least is 3 and at most is 5.
    if (argc < 3 || argc > 5) {
        throwOutOfRangeArguments();
    }

    // Is the pattern within MAX_PATTERN_CHARACTERS?
    int index = 0;
    while ((argv[1])[index] != '\0') {
        index++;
    }

    if (index > MAX_PATTERN_CHARACTERS || index < 0) {
        throwOutOfRangePattern();
    }

    // Were there any errors finding the file's name?  Does it include the .txt extension or is it NULL?
    const char *filename = argv[2];
    FILE *fptr = fopen(filename, "r");
    checkFile(fptr, filename);

    // Are there any other optional flags used?
    switch (argc) {
        case 4:
            if (strcmp((argv[3])[1], 'i') == 1) {
                *isCaseInsensitive = 1;
            }
            else if ((strcmp((argv[3])[1], 'n') == 1)) {
                *isLineNumber = 1;
            }
            break;
        case 5:
            if ((strcmp((argv[3])[1], 'i') == 1) && (strcmp((argv[4])[1], 'n') == 1)) {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;
            }
            else if ((strcmp((argv[3])[1], 'n') == 1) && (strcmp((argv[4])[1], 'i') == 1)) {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;
            }
            break;
        default:
            throwInvalidFlag();
            break;
    }
}

void checkFile(FILE *fptr, const char *filename) {
    if (fptr == NULL) {
        printf("Failed to open %s\n", filename);
        exit(1);
    }
}

void throwInvalidFlag() {
    printf("Usage: ./main <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number\n");
    exit(1);
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

