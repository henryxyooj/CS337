#include "file.h"
#include "throws.c"

void grepPlus(int argc, char *argv[]) {
    int isCase = 0, isLines = 0;
    char path[PATH_SIZE] = "."; // default path

    checkTerminalInputs(argc, argv, &isCase, &isLines, path);

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror(path);
        exit(1);
    }

    struct dirent *entry;
    char pattern[BUFFER_SIZE];
    strcpy(pattern, argv[3]);
    //pid_t pids[MAX_FILES];

    while ((entry = readdir(dir)) != NULL) {
        // check each entry to see if they're a text file
        // if it is a text file, increment the file count and check with MAX_FILES
        // create a pid and also a pid counter to display the amount of processes that was created
        if (strstr(entry->d_name, ".txt")) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);

    // display the results
}


 void checkTerminalInputs(int argc, char *argv[], int *isCase, int *isLines, char path[PATH_SIZE]) {
    // validate terminal inputs: [dir] [pattern] [case insens [-i]] or [num of lines [-n]]
    // check to see how many arguments there are
    if (argc > 7 || argc < 4) {
        throwOutOfBoundsTerminalInputs();
    }

    // is the dir input valid?
    // stores the directory string into variable dir, then checks the base case of it not being "." for some reason
    char dir[BUFFER_SIZE];
    strcpy(dir, argv[2]);
    if (dir[0] != '.') {
        throwInvalidDirectory(dir);
    }
    else if (dir[0] != '.' && dir[1] != '/') {
        throwInvalidDirectory(dir);
    }

    // Is the pattern within MAX_PATTERN_CHARACTERS?
    int index = 0;
    while ((argv[3])[index] != '\0') {
        index++;
    }

    if (index > MAX_PATTERN_CHARACTERS || index < 0) {
        throwOutOfBoundsPattern();
    }

    // if argc = 6, are both either i or n?
    // if argc = 5, which flag is it?
    if (argc > 4) {
        for (int i = 4; i < argc; i++) {
            // checks to see for double flag entry incase of: ./main grep . once -n -n
            if ((strcmp(argv[i], "-n") == 0) && (strcmp(argv[i - 1], "-n") != 0)) {
                *isLines = 1;
            }
            // checks to see for double flag entry incase of: ./main grep . once -i -i
            else if ((strcmp(argv[i], "-i") == 0) && (strcmp(argv[i - 1], "-i") != 0)) {
                *isCase = 1;
            }
            else {
                throwInvalidFlagOption();
            }
        }
    }
 }