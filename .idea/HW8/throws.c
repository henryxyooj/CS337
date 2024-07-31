/*******************************************************************
* Author: Henry Xiong
* Date: July 30, 2024

* Description:
* This C program contains all of the error handling for the pipe.c program

Usage:
* include this file with pipe.c to make sure any errors that may occur in pipe.c will throw errors to the user when inputting
* any wrong input or if any thing at all
*******************************************************************/
void throwOutOfBoundsTerminalInputs();
void throwInvalidCommand();
void throwInvalidPipe();
void throwInvalidFlag();
void throwPipeError();
void throwProcessError();
void throwArgError();
void throwExecvpError();

/*******************************************************************
* Description: if the user inputted too many arguments to the terminal
*******************************************************************/
void throwOutOfBoundsTerminalInputs() {
    puts("Error: Invalid amount of arguments to the terminal.");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

/*******************************************************************
* Description: throws an error if a user doesn't input any of the two
                commands: sort or wc
*******************************************************************/
void throwInvalidCommand() {
    puts("Error: pipe.c currently supports only these two commands: \"wc\" or \"sort\"");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

/*******************************************************************
* Description: throws an error if the user doesn't input the pipe operator
                correctly to the terminal
*******************************************************************/
void throwInvalidPipe() {
    puts("Error: Use the pipe command with either: \"|\" or \'|\'");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

/*******************************************************************
* Description: throws an error if a user doesn't input any of the supported
                flags: -l, -w, -c
*******************************************************************/
void throwInvalidFlag() {
    puts("Error: pipe.c currently supports only these flags for wc command: [-l], [-w], or [-c]");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

/*******************************************************************
* Description: throws an error if there's a problem when creating a pipe
*******************************************************************/
void throwPipeError() {
    puts("Error piping.");
    exit(1);
}

/*******************************************************************
* Description: throws an error if there's a problem when creating a new process
*******************************************************************/
void throwProcessError() {
    puts("Error creating child process.");
    exit(1);
}

/*******************************************************************
* Description: shouldn't happen at all with all of the safety nets before this,
                but before the execvp function, if there's any problem at all, throw this error
*******************************************************************/
void throwArgError() {
    puts("Error building arguments for cat command.");
    exit(1);
}

/*******************************************************************
* Description: throws an error after the execvp function if for some reason
                it's still going
*******************************************************************/
void throwExecvpError() {
    puts("Error with execvp function.");
    exit(1);
}