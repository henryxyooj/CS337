/*******************************************************************
* Author: Henry Xiong
* Date: July 24, 2024

* Description: 
* This C program implements a modified version of the grep command-line utility using fork, exec, and wait system calls. 

Usage:
* Compile it using a C compiler and run the executable from the command line with appropriate arguments.
*    - To search for a pattern in text files: ./main grep [directory] [pattern] [i] [-n]
*******************************************************************/

#include "file.h"
#include "throws.c"

#define PATH_SIZE 1024
#define BUFFER_SIZE 1024
#define MAX_PATTERN_CHARACTERS 10
#define MAX_FILES 5

void grepPlus(int argc, char *argv[]);
void checkTerminalInputs(int argc, char *argv[], int *isCase, int *isLines, char path[PATH_SIZE]);
void throwOutOfBoundsTerminalInputs();
void throwOutOfBoundsPattern();
void throwInvalidDirectory(char dir[BUFFER_SIZE]);
void throwInvalidFlagOption();
void throwErrorForking();


/*******************************************************************
* Description: Simulates a limited set of behavior of the grep command by taking user input 
                from the terminal and looks for the specified pattern and matches with
                the text files within the directories
*******************************************************************/
void grepPlus(int argc, char *argv[]) {
    int isCase = 0, isLines = 0;
    char path[PATH_SIZE] = "."; // default path

    checkTerminalInputs(argc, argv, &isCase, &isLines, path);

    //  check to see if it's a valid path, if not exit the program
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror(path);
        exit(1);
    }

    struct dirent *entry;
    pid_t pids[MAX_FILES];
    char pattern[BUFFER_SIZE];
    char pathStringBuilder[BUFFER_SIZE]; 
    int fileCount = 0, pidIndex = 0;

    strcpy(pattern, argv[3]);

    while ((entry = readdir(dir)) != NULL) {  
        // check each entry to see if they're a text file
        // if it is a text file, increment the file count and check with MAX_FILES
        // create a pid and also a pid counter to display the amount of processes that was created
        if (strstr(entry->d_name, ".txt")) {    // currently looking at .txt files
            fileCount++;
            
            // max process is 5 only, break out of the loop if over capacity
            if (fileCount > MAX_FILES) {
                break;
            }

            // fork now that everything fits the requirements to split up processes reading the text files
            pids[pidIndex] = fork();
            if (pids[pidIndex] < 0) {
                throwErrorForking();
            }
            
            if (pids[pidIndex] == 0) {  // in child process
                // create an absolute path with the current information 
                strcat(pathStringBuilder, path);
                strcat(pathStringBuilder, "/");
                strcat(pathStringBuilder, entry->d_name);

                // similar to lab7, we can put each flag/input into pointer array to then call the execvp function
                char *grepArgs[] = {"grep", pathStringBuilder, pattern, NULL, NULL, NULL};

                //  if isLines was true, replace NULL with nH or n
                if (isLines == 1) {
                    grepArgs[3] = "-nH";
                }
                else {
                    grepArgs[3] = "-H";
                }

                //  if isCase was true, replace NULL with -i
                if (isCase == 1) {
                    grepArgs[4] = "-i";
                }

                execvp("grep", grepArgs);
                perror("execvp");
                exit(1);
            }

            pidIndex++;
        }
    }

        // wait for each of the child processes to get done
        for (int i = 0; i < pidIndex; i++) {
            waitpid(pids[i], NULL, 0);
        }

        // sometimes the results won't display correctly, use fflush to clean it up
        fflush(stdout);

        // print out the PIDS of each child process
        printf("Child process PIDs: ");
        for (int i = 0; i < pidIndex; i++) {
            printf("%d ", pids[i]);
        }

        printf("\nNumber of files searched: %d\n", fileCount);
        printf("Number of processes created: %d\n", pidIndex);
    
    closedir(dir);
}


 void checkTerminalInputs(int argc, char *argv[], int *isCase, int *isLines, char path[PATH_SIZE]) {
    // validate terminal inputs: [dir] [pattern] [case insens [-i]] or [num of lines [-n]] 
    // check to see how many arguments there are
    if (argc > 7 || argc < 4) {
        throwOutOfBoundsTerminalInputs();
    }

    // is the dir input valid?
    // stores the directory string into variable dir, then checks the base case of it not being "." 
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

// if a flag is used incorrectly, throw an error
void throwInvalidFlagOption() {
    puts("Error: Flag(s) used aren't valid.");
    puts("Usage: [./main] [grep] [directory] [pattern] [optional flag: -i or -n] [optional flag: -i or -n]");
    puts("Usage: Case insensitive = [-i]\t Print line numbers = [-n]");
    exit(1);
}

// in the case where forking isn't done correctly, throw an error
void throwErrorForking() {
    printf("Error: Forking failed.\nUsage: Try running grep again.\n");
    exit(1);
}
