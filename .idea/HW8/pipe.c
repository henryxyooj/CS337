#include "file.h"
#include "throws.c"

void checkTerminal(int argc, char *argv[]);
void checkTerminalArguments(int argc);
void checkProcess(pid_t process);

void pipe_commands(int argc, char *argv[]) {
    // check user input
    checkTerminal(argc, argv);

    // create a pipe for process communication
    int fd[2];
    checkPipe(fd);

    // create two child processes
    pid_t c1pid = fork();
    checkProcess(c1pid);

    pid_t c2pid = fork();
    checkProcess(c2pid);

    // use pipe to create communication channels between processes
        // use dup in every child process to connect the appropriate STDIN/STDOUT to the pipe read/write end

    // use the execvp function to execute each of the commands in each child passing necessary flags
        // call for wc and sort, handled with dup, use it before execvp

}

void checkTerminal(int argc, char *argv[]) {
    checkTerminalArguments(argc);

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

void checkTerminalArguments(int numArgs) {
    if (argc > 7 || argc < 5) {
        throwOutOfBoundsTerminalInputs();
    }
}

 void checkPipe(int fd) {
    if (pipe(fd) == -1) {
        throwPipeError();
    }
}
void checkProcess(pid_t process) {
    if (process == -1) {
        throwProcessError();
    }
}