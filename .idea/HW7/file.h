#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

void grepPlus(int argc, char *argv[]);

void throwOutOfBoundsTerminalInputs();
void throwOutOfBoundsPattern();
void throwInvalidDirectory();
