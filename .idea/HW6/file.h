#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define PATH_SIZE 1024

void lsExtended(int argc, char *argv[]);

void checkFlags(int argc, char *argv[], int *isAllFiles, int *isVisibleFilesInDirectory, int *isAllFilesInDirectory, char path[PATH_SIZE]);

void throwInvalidFlag();