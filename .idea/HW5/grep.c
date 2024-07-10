
// citations:
// https://www.tutorialspoint.com/c-program-to-convert-a-number-to-a-string
// used to figure out how to convert an integer into a string, had an error with the strcat function
// where it wasn't adding to my lineBuilder because it was of type int, so I couldn't append it

#include "text.h"

void grepLite(int argc, char *argv[]) {
    int isCaseInsensitive = 0;
    int isLineNumber = 0;
    int isMatched = 0;
    int isWriteToFile = 0;

    checkTerminalInputs(argc, argv, &isCaseInsensitive, &isLineNumber, &isWriteToFile);

    // open and read the file
    const char *filename = argv[2];
    FILE *fptr = fopen(filename, "r");
    checkFile(fptr, filename);

    // set up variables to store the line and it's line number
    char stringBuilder[MAX_CHARACTERS] = "";
    char line[MAX_CHARACTERS];
    int lineNumber = 0;

    // read through each line from the text file
    while (fgets(line, MAX_CHARACTERS, fptr)) {
        char lineOriginal[MAX_CHARACTERS];
        strcpy(lineOriginal, line);
        // when reading from a text file, the last character of the line is '\n'
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        if (isCaseInsensitive == 1) {
            // copies the pattern from the text file into another variable
            char lowerLine[MAX_CHARACTERS];
            strcpy(lowerLine, lineOriginal);
            toLowerCase(lowerLine);

            // copies the pattern from terminal into another variable
            char lowerPattern[MAX_CHARACTERS];
            strcpy(lowerPattern, argv[1]);
            toLowerCase(lowerPattern);

            // use the substring to check if lowered pattern is inside of lowered line and if isLineNumber true or false
            if (strstr(lowerLine, lowerPattern)) {
                isMatched = 1;
                if (isLineNumber == 1) { // if user picked the option to display the line number
                    // convert the lineNumber of type int into a string
                    char lineNumberToStrCase[MAX_CHARACTERS];
                    sprintf(lineNumberToStrCase, "%d ", (lineNumber + 1));
                    strcat(stringBuilder, lineNumberToStrCase);
                }
                strcat(stringBuilder, lineOriginal);
                strcat(stringBuilder, "\n");
            }
        }
        else {  // not case insensitive and also check for if isLineNumber is valid too
            if (strstr(line, argv[1])) {
                isMatched = 1;
                if (isLineNumber == 1) {
                    char lineNumberToStrNotCase[MAX_CHARACTERS];
                    sprintf(lineNumberToStrNotCase, "%d ", (lineNumber + 1));
                    strcat(stringBuilder, lineNumberToStrNotCase);
                }
                strcat(stringBuilder, line);
                strcat(stringBuilder, "\n");
            }
        }

        lineNumber++;
    }

    fclose(fptr);

    messageToChoice(isWriteToFile, stringBuilder, argv, isMatched);
}

void checkTerminalInputs(int argc, char *argv[], int *isCaseInsensitive, int *isLineNumber, int *isWriteToFile) {
    // Is the amount of arguments from terminal valid? At least is 3 and at most is 7.
    if (argc < 3 || argc > 7) {
        throwOutOfRangeArguments();
        if (argc == 6) {
            throwInvalidOutputFileName();
        }
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
    checkFlag(argc, argv, isCaseInsensitive, isLineNumber, isWriteToFile);
}

void checkFile(FILE *fptr, const char *filename) {
    if (fptr == NULL) {
        printf("Error: Failed to open %s\n", filename);
        exit(1);
    }
}

void checkFlag(int argc, char *argv[], int *isCaseInsensitive, int *isLineNumber, int *isWriteToFile) {
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
        case 6:
            if ((argv[3])[1] == 'i' && (argv[4])[1] == 'n' && (argv[5])[0] == '>') {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;

                throwInvalidOutputFileName();
            }
            else if ((argv[3])[1] == 'n' && (argv[4])[1] == 'i' && (argv[5])[0] == '>') {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;

                throwInvalidOutputFileName();
            }
            else {
                throwInvalidFlag();
            }
            break;
        case 7:
            if ((argv[3])[1] == 'i' && (argv[4])[1] == 'n' && (argv[5])[0] == '>') {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;

                const char *fileout = argv[6];
                FILE *foptr = fopen(fileout, "w");
                checkFile(foptr, fileout);
                fclose(foptr);
                *isWriteToFile = 1;
            }
            else if ((argv[3])[1] == 'n' && (argv[4])[1] == 'i' && (argv[5])[0] == '>') {
                *isCaseInsensitive = 1;
                *isLineNumber = 1;

                const char *fileout = argv[6];
                FILE *foptr = fopen(fileout, "w");
                checkFile(foptr, fileout);
                fclose(foptr);
                *isWriteToFile = 1;
            }
            else {
                throwInvalidFlag();
            }
            break;
    }
}

void toLowerCase(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if ((str[i] >= 'A' && str[i] <= 'Z')) {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

void messageNoPatternFound() {
    printf("No matches are found.\n");
    exit(1);
}

void messageToChoice(int isWriteToFile, char stringBuilder[], char *argv[], int isMatched) {
    if (isWriteToFile == 1) {
        const char *fileout = argv[6];
        FILE *foptr = fopen(fileout, "w");
        checkFile(foptr, fileout);

        fprintf(foptr, "%s", stringBuilder);
        fclose(foptr);
    }
    else {
        if (isMatched == 0) {
            messageNoPatternFound();
        }
        printf("%s", stringBuilder);
    }
}

void throwInvalidFlag() {
    printf("Usage: ./main <pattern> <filename> <-i/-n> <-i/-n> [<] <fileout>\n");
    printf("Usage: Both <-i/-n> are optional, [-i] for case insensitive search and [-n] for line number.\n");
    printf("Usage: When using \"<\", type in a new file name to write in <fileout>.\n");
    exit(1);
}

void throwInvalidPattern() {
    printf("Usage: ./main <pattern> <filename> <-i/-n> <-i/-n> [<] <fileout>\n");
    printf("Usage: Both <-i/-n> are optional, [-i] for case insensitive search and [-n] for line number.\n");
    printf("Usage: When using \"<\", type in a new file name to write in <fileout>.\n");
    printf("Usage: <pattern> must be a single word you want to find within the desired file.\n");
    exit(1);
}

void throwInvalidFileName() {
    printf("Usage: ./main <pattern> <filename> <-i/-n> <-i/-n> [<] <fileout>\n");
    printf("Usage: Both <-i/-n> are optional, [-i] for case insensitive search and [-n] for line number.\n");
    printf("Usage: When using \"<\", type in a new file name to write in <fileout>.\n");
    printf("Usage: <filename> must have the extension \".txt\" after the file's name.\n");
    exit(1);
}

void throwInvalidOutputFileName() {
    printf("Usage: ./main <pattern> <filename> <-i/-n> <-i/-n> [<] <fileout>\n");
    printf("Usage: Both <-i/-n> are optional, [-i] for case insensitive search and [-n] for line number.\n");
    printf("Usage: When using \"<\", type in a new file name to write in <fileout>.\n");
    printf("Error: Invalid output file name.\n");
    exit(1);
}

void throwOutOfRangeArguments() {
    printf("Usage: ./main <pattern> <filename> <-i/-n> <-i/-n> [<] <fileout>\n");
    printf("Usage: Both <-i/-n> are optional, [-i] for case insensitive search and [-n] for line number.\n");
    printf("Usage: When using \"<\", type in a new file name to write in <fileout>.\n");
    printf("Error: Your arguments are out of range.");
    exit(1);
}

void throwOutOfRangePattern() {
    printf("Usage: Pattern can only be 10 characters long.\n");
    exit(1);
}

