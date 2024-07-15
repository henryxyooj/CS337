#include "file.h"

void lsExtended(int argc, char *argv[]){
   checkFlags(argc, argv);

}

void checkFlags(int argc, char *argv[]) {
   // check for any flags with a switch statement
   // a, l, la, none; default = throw error
   int isValidFlag = 0;

   // search through each argv value depending on the argc value
   for (int i = 0; i < argc; i++) {
      // check if it has the "-" to denote that it's a flag
      if (argv[i][0] != '-') {
         throwInvalidFlag();
      }

      // then compare the char/string to see if it's actually a valid flag
      switch ((argv[i])[1]) {
         case 'a':

            break;
         case 'l':
            break;
         case 'la':
            break;
         default:
            throwInvalidFlag();
            break;
      }
   }
}

void throwInvalidFlag() {
    printf("Usage: ./minils <optional command> <optional path>\n");
    printf("Note: Optional command includes: -l, -a, or -la\nNote: Optional path is your own path.");
    exit(1);
}