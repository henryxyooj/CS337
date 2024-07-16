#include "file.h"

void lsExtended(int argc, char *argv[]){
   int isAllFiles = 0;                  // display all files and directories, including hidden ones; -a
   int isVisibleFiles = 0;   // display all visible files and directories in the specified path; -l
   char path[PATH_SIZE] = ".";

   checkFlags(argc, argv, &isAllFiles, &isVisibleFiles, path);

   printf("%s\n", path);

}

void checkFlags(int argc, char *argv[], int *isAllFiles, int *isVisibleFiles, char path[PATH_SIZE]) {
   int isFlagged = 0;   // use this to get to base case

   // search through each argv value depending on the argc value
   for (int i = 1; i < argc; i++) {
      // check if it has the "-" to denote that it's a flag
      if (argv[i][0] != '-') {
         throwInvalidFlag();
      }

      // then compare the char/string to see if it's actually a valid flag
      if (strcmp(argv[i], "-a") == 0) {
         *isAllFiles = 1;
      }
      else if (strcmp(argv[i], "-l") == 0) {
         *isVisibleFiles = 1;
      }
      else if (strcmp(argv[i], "-la") == 0) {
         *isAllFiles = 1;
         *isVisibleFiles =1;
      }
      else {
         throwInvalidFlag();
      }

      if (isFlagged == 0) {
         path = argv[1];
      }
   }
}

void getFiles(char path[PATH_SIZE], int isAllFiles, int isVisibleFiles) {
   DIR *dir = opendir(path);
   if (dir == NULL) {
      perror(path);
      exit(1);
   }

   struct dirent *entry;
   while ((entry = readdir(dir)) != NULL) {
      printf("%s ", entry -> d_name);
   }

   closedir(dir);
}

void throwInvalidFlag() {
    printf("Usage: ./minils <optional command> <optional path>\n");
    printf("Note: Optional command includes: -l, -a, or -la\nNote: Optional path is your own path.");
    exit(1);
}