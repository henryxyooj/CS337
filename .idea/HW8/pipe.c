#include "file.h"
#include "throws.c"

#define MAX_CHAR 1024

void checkTerminal(int argc, char *argv[], int *isWc, int *isSort, int *isNumOfLines, int *isWordCount, int *isNumOfBytes);
void checkTerminalArguments(int argc);
//void checkTerminalPipe(char *argv[]);
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

    if (c1pid == 0) {   // first child process, you're "writing"
        close(fd[0]);   // close read
        dup2(fd[0], STDOUT_FILENO);
        close(fd[1]);   // close write

        char *c1PidArgs[] = {"cat", argv[2], NULL};

        execvp("cat", c1PidArgs);
        throwExecvpError();
    }

    // create second child process
    pid_t c2pid = fork();
    checkProcess(c2pid);

    if (c2pid == 0) { // Second child process, you're "reading"
        close(fd[1]); // Close write
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); // Close read

        char *c2PidArgs[] = {NULL, NULL, NULL, NULL};

        if (isWc == 1) {
            c2PidArgs[0] = "wc";
            c2PidArgs[1] = argv[5];
            execvp("wc", c2PidArgs);
        }
        else if (isSort == 1) {
            c2PidArgs[0] = "sort";
            execvp("sort", c2PidArgs);checkTerminalCommandFlag(argv, isNumOfLines, isWordCount, isNumOfBytes);
        }
        else {
            throwArgError();
        }
        throwExecvpError();
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(c1pid, NULL, 0);
    waitpid(c2pid, NULL, 0);
}

void checkTerminal(int argc, char *argv[], int *isWc, int *isSort, int *isNumOfLines, int *isWordCount, int *isNumOfBytes) {
    checkTerminalArguments(argc);
    checkTerminalFilename(argv);
    //checkTerminalPipe(argv);
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
    char flag[MAX_CHAR];
    strcpy(flag, argv[5]);

    if (strcmp(command, "wc") == 0) {
        if (argv[5] == NULL && strcmp(argv[5], "-l") == 0 &&
            strcmp(argv[5], "-w") == 0 && strcmp(argv[5], "-c")) {
                *isWc = 1;
                checkTerminalCommandFlag(argv, isNumOfLines, isWordCount, isNumOfBytes);
            }
        else {
            throwInvalidFlag();
        }
    }
    else if (strcmp(command, "sort") == 0) {
        *isSort = 1;
    }
    else {
        throwInvalidCommand();
    }
}

/*
void checkTerminalPipe(char *argv[]) {
    char pipeCmd[MAX_CHAR];
    strcpy(pipeCmd, argv[4]);

    if (strcmp(pipeCmd, "|") != 0 && strcmp(pipeCmd, "'|'") != 0) {
        throwInvalidPipe();
    }
}
*/

void checkTerminalFilename(char *argv[]) {
    char filename[MAX_CHAR];
    strcpy(filename, argv[2]);

    // https://www.youtube.com/watch?v=S5h3BYg8988&ab_channel=linuxhint
    struct stat buffer;
    if (stat(filename, &buffer) != 0) {
        puts("Error occurred\n");
        exit(1);
    }
}

void checkTerminalArguments(int argc) {
    if (argc > 6 || argc < 5) {
        throwOutOfBoundsTerminalInputs();
    }
}

void checkProcess(pid_t process) {
    if (process == -1) {
        throwProcessError();
    }
}