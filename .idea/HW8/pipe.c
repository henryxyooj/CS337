#include "file.h"
#include "throws.c"

#define MAX_CHAR 1024

void checkTerminal(int argc, char *argv[], int *isWc, int *isSort, int *isNumOfLines, int *isWordCount, int *isNumOfBytes);
void checkTerminalArguments(int argc);
void checkTerminalPipe(char *argv[]);
void checkTerminalCommand(int *isWc, int *isSort, char *argv[], int *isNumOfLines, int *isWordCount, int *isNumOfBytes);
void checkTerminalCommandFlag(char *argv[], int *isNumOfLines, int *isWordCount, int *isNumOfBytes);
void checkTerminalFilename(char *argv[]);

void checkProcess(pid_t process);

void pipe_commands(int argc, char *argv[]) {
    int isWc = 0, isSort = 0;
    int isNumOfLines = 0, isWordCount = 0, isNumOfBytes = 0;

    // check user input
    checkTerminal(argc, argv, &isWc, &isSort, &isNumOfLines, &isWordCount, &isNumOfBytes);

    // create a pipe for process communication
    int fd[2];
    if (pipe(fd) == -1) {
        throwPipeError();
    }

    // create two child processes
    pid_t c1pid = fork();
    checkProcess(c1pid);

    pid_t c2pid = fork();
    checkProcess(c2pid);

    // use pipe to create communication channels between processes
        // use dup in every child process to connect the appropriate STDIN/STDOUT to the pipe read/write end

    // use the execvp function to execute each of the commands in each child passing necessary flags
        // call for wc and sort, handled with dup, use it before execvp

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}

void checkTerminal(int argc, char *argv[], int *isWc, int *isSort, int *isNumOfLines, int *isWordCount, int *isNumOfBytes) {
    checkTerminalArguments(argc);
    checkTerminalFilename(argv);
    checkTerminalPipe(argv);
    checkTerminalCommand(isWc, isSort, argv, isNumOfLines, isWordCount, isNumOfBytes);
}

void checkTerminalCommandFlag(char *argv[], int *isNumOfLines, int *isWordCount, int *isNumOfBytes) {
    char flag[MAX_CHAR];
    strcpy(flag, argv[5]);

    if (strcmp(flag, "-l") == 0) {  // number of lines
        *isNumOfLines = 1;
    }
    else if (strcmp(flag, "-w") == 0) { // number of words
        *isWordCount = 1;
    }
    else if (strcmp(flag, "-c") == 0) { // number of bytes
        *isNumOfBytes = 1;
    }
    else {
        throwInvalidFlag();
    }
}

void checkTerminalCommand(int *isWc, int *isSort, char *argv[], int *isNumOfLines, int *isWordCount, int *isNumOfBytes) {
    char command[MAX_CHAR];
    strcpy(command, argv[4]);

    if (strcmp(command, "wc") == 0) {
        *isWc = 1;
    }
    else if (strcmp(command, "sort") == 0) {
        *isSort = 1;
    }
    else {
        throwInvalidCommand();
    }

    checkTerminalCommandFlag(argv, isNumOfLines, isWordCount, isNumOfBytes);
}

void checkTerminalPipe(char *argv[]) {
    char pipeCmnd[MAX_CHAR];
    strcpy(pipeCmnd, argv[3]);

    if (strcmp(pipeCmnd, "\"|\"") != 0 || strcmp(pipeCmnd, "\'|\'") != 0) {
        throwInvalidPipe();
    }
}

void checkTerminalFilename(char *argv[]) {
    char filename[MAX_CHAR];
    strcpy(filename, argv[2]);


}

void checkTerminalArguments(int argc) {
    if (argc > 7 || argc < 5) {
        throwOutOfBoundsTerminalInputs();
    }
}

void checkProcess(pid_t process) {
    if (process == -1) {
        throwProcessError();
    }
}