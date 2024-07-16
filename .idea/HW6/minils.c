#include "file.h"

void lsExtended(int argc, char *argv[]){
   int isAllFiles = 0;                  // display all files and directories, including hidden ones; -a
   int isVisibleFilesInDirectory = 0;   // display all visible files and directories in the specified path; -l
   int isAllFilesInDirectory = 0;       // display all hidden files and directories; -la
   char path[PATH_SIZE];

   checkFlags(argc, argv, &isAllFiles, &isVisibleFilesInDirectory, &isAllFilesInDirectory, path);

   printf("%s\n", path);

}

void checkFlags(int argc, char *argv[], int *isAllFiles, int *isVisibleFilesInDirectory, int *isAllFilesInDirectory, char path[PATH_SIZE]) {
   // a, l, la, none; default = throw error

   // search through each argv value depending on the argc value
   for (int i = 0; i < argc; i++) {
      // check if it has the "-" to denote that it's a flag
      if (argv[i][0] != '-') {
         throwInvalidFlag();
      }

      // then compare the char/string to see if it's actually a valid flag
      if (strcmp(argv[i], "-a") == 0) {
         *isAllFiles = 1;
      }
      else if (strcmp(argv[i], "-l") == 0) {
         *isVisibleFilesInDirectory = 1;
      }
      else if (strcmp(argv[i], "-la") == 0) {
         *isAllFilesInDirectory =1;
      }
      else {
         throwInvalidFlag();
      }

      // base case of no flag
      path = argv[1];
   }
}

void throwInvalidFlag() {
    printf("Usage: ./minils <optional command> <optional path>\n");
    printf("Note: Optional command includes: -l, -a, or -la\nNote: Optional path is your own path.");
    exit(1);
}