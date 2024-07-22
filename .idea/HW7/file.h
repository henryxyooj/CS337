#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

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