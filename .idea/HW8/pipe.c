/*******************************************************************
* Author: Henry Xiong
* Date: July 30, 2024

* Description:
* This C program implements the following piped unix commands:
* cat file | wc -l
* cat file | wc -w
* cat file | wc -c
* cat file | sort

Usage:
* Compile it using a C compiler and run the executable from the command line with appropriate arguments.
* The format required to input it into the terminal is: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]

Citations:
* https://www.youtube.com/watch?v=S5h3BYg8988&ab_channel=linuxhint
I had a rough time trying to find ways to open up the file.  This video
helped me understand it better, but I'm going to review it again this weekend
along with his code near around the 3:10 mark.  I sort of get that having the buffer for the
second parameter holds the information of the file, but I understand the first parameter
which is just the file's name.  By inputting in something like ./mydir/trees.txt, you're giving the
absolute path to the file, so it makes sense.  Correct me if I'm wrong.
*******************************************************************/

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

/*******************************************************************
* Description: creates two processes that directs output from child 1 to child 2
*               it already creates the beginning portion of the command,
                so the child 2 process finishes the other half of the full command
*******************************************************************/
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
        dup2(fd[1], STDOUT_FILENO);
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

        // if wc is the command being called for, check for which flag is being used and execute it
        // otherwise check to see if it's sort and execute it
        // if not either of those, throw an error
        if (isWc == 1) {
            c2PidArgs[0] = "wc";
            c2PidArgs[1] = argv[5];
            execvp("wc", c2PidArgs);
        }
        else if (isSort == 1) {
            c2PidArgs[0] = "sort";
            execvp("sort", c2PidArgs);
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

/*******************************************************************
* Description: Checks each input in the terminal to correctly set up
                the pipe
*******************************************************************/
void checkTerminal(int argc, char *argv[], int *isWc, int *isSort, int *isNumOfLines, int *isWordCount, int *isNumOfBytes) {
    checkTerminalArguments(argc);
    checkTerminalFilename(argv);
    checkTerminalPipe(argv);
    checkTerminalCommand(isWc, isSort, argv, isNumOfLines, isWordCount, isNumOfBytes);
}

/*******************************************************************
* Description: part of the checkTerminalCommand, it checks out to see
                if argv[5] is a valid flag used for this mini pipe program
*******************************************************************/
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

/*******************************************************************
* Description: Checks to see if the command requested by user is either
                wc or sort
*******************************************************************/
void checkTerminalCommand(int *isWc, int *isSort, char *argv[], int *isNumOfLines, int *isWordCount, int *isNumOfBytes) {
    if (strcmp(argv[4], "wc") == 0) {
        *isWc = 1;
        if (argv[5] != NULL) {
                checkTerminalCommandFlag(argv, isNumOfLines, isWordCount, isNumOfBytes);
            }
        else {
            throwInvalidFlag();
        }
    }
    else if (strcmp(argv[4], "sort") == 0) {
        *isSort = 1;
    }
    else {
        throwInvalidCommand();
    }
}

/*******************************************************************
* Description: Checks to see if the user correctly inputted the pipe
                operator into the terminal
*******************************************************************/
void checkTerminalPipe(char *argv[]) {
    if ((strcmp(argv[3], "|") != 0) && (strcmp(argv[3], "'|'") != 0)) {
        throwInvalidPipe();
    }
}

/*******************************************************************
* Description: Searches for the pattern given from terminal to the requested
                file
*******************************************************************/
void checkTerminalFilename(char *argv[]) {
    char filename[MAX_CHAR];
    strcpy(filename, argv[2]);

    // https://www.youtube.com/watch?v=S5h3BYg8988&ab_channel=linuxhint
    struct stat buffer;
    if (stat(filename, &buffer) != 0) {
        puts("Error occurred opening the %s\n", filename);
        exit(1);
    }
}

/*******************************************************************
* Description: Checks to see if the amount of arguments inputted by the
                user is valid
*******************************************************************/
void checkTerminalArguments(int argc) {
    if (argc > 6 || argc < 5) {
        throwOutOfBoundsTerminalInputs();
    }
}

/*******************************************************************
* Description: checks to see if there's anything wrong when creating
                a new process
*******************************************************************/
void checkProcess(pid_t process) {
    if (process == -1) {
        throwProcessError();
    }
}