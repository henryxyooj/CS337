
// citations:
// https://www.tutorialspoint.com/c-program-to-convert-a-number-to-a-string
// used to figure out how to convert an integer into a string, had an error with the strcat function
// where it wasn't adding to my lineBuilder because it was of type int, so I couldn't append it

#include "text.h"

void grepLite(int argc, char *argv[]) {
    int isCaseInsensitive = 0;
    int isLineNumber = 0;

    checkTerminalInputs(argc, argv, &isCaseInsensitive, &isLineNumber);

    // open and read the file
    const char *filename = argv[2];
    FILE *fptr = fopen(filename, "r");
    checkFile(fptr, filename);

    // read through each line
    char stringBuilder[MAX_CHARACTERS];
    char lineBuilder[MAX_CHARACTERS];
    char line[MAX_CHARACTERS];
    int lineNumber = 0;

    while (fgets(line, MAX_CHARACTERS, fptr)) {
        if (isCaseInsensitive == 1) {
            // lower all chars from the file
            char lowerLine[MAX_CHARACTERS];
            int indexLine = 0;
            strcpy(lowerLine, line);
            while (lowerLine[indexLine] != '0') {
                if ((lowerLine[indexLine] >= 'A' && lowerLine[indexLine] <= 'Z')) {
                    lowerLine[indexLine] = lowerLine[indexLine] + 32;
                }
                indexLine++;
            }

            // lower all chars from the terminal
            char lowerPattern[MAX_CHARACTERS];
            int indexPattern = 0;
            strcpy(lowerPattern, line);
            while (lowerPattern[indexPattern] != '0') {
                if ((lowerPattern[indexPattern] >= 'A' && lowerPattern[indexPattern] <= 'Z')) {
                    lowerPattern[indexPattern] = lowerPattern[indexPattern] + 32;
                }
                indexPattern++;
            }

            // use the substring to check if lowered pattern is inside of lowered line and if isLineNumber true or false
            if (strstr(lowerLine, lowerPattern)) {
                if (isLineNumber == 1) {
                    char lineNumberToStrCase[MAX_CHARACTERS];
                    sprintf(lineNumberToStrCase, "%d: ", lineNumber);
                    strcat(stringBuilder, line);
                    strcat(lineBuilder, lineNumberToStrCase);
                }
                else {
                    strcat(stringBuilder, line);
                }
            }
            else {
                messageNoPatternFound();
            }
        }
        else {  // not case insensitive and also check for if isLineNumber is valid too
            if (strstr(line, argv[1])) {
                if (isLineNumber == 1) {
                    char lineNumberToStrNotCase[MAX_CHARACTERS];
                    sprintf(lineNumberToStrNotCase, "%d: ", lineNumber);
                    strcat(stringBuilder, line);
                    strcat(lineBuilder, lineNumberToStrNotCase);
                }
                else {
                    strcat(stringBuilder, line);
                }
            }
            else {
                messageNoPatternFound();
            }
        }

        lineNumber++;
    }

    fclose(fptr);
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
    fclose(fptr);

    // Are there any other optional flags used?
    switch (argc) {
        case 4:
            if ((argv[3])[1] == 'i') {
                *isCaseInsensitive = 1;
            }
            else if ((argv[3])[1] == 'n') {
                *isLineNumber = 1;
            }
            else {
                throwInvalidFlag();
            }
            break;
        case 5:
            if ((argv[3])[1] == 'i' && (argv[4])[1] == 'n') {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;
            }
            else if ((argv[3])[1] == 'n' && (argv[4])[1] == 'i') {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;
            }
            else {
                throwInvalidFlag();
            }
            break;
    }
}

void checkFile(FILE *fptr, const char *filename) {
    if (fptr == NULL) {
        printf("Error: Failed to open %s\n", filename);
        exit(1);
    }
}

void messageNoPatternFound() {
    printf("No matches are found.\n");
    exit(1);
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

