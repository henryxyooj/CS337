/*******************************************************************
* Author: Sadia Nowrin
* Date: April 2, 2024

* Description:
* This C program implements a modified version of the grep command-line utility using fork, exec, and wait system calls.

Usage:
* Compile it using a C compiler and run the executable from the command line with appropriate arguments.
*    - To search for a pattern in text files: ./main grep [directory] [pattern] [i] [-n]
*******************************************************************/

#include "file.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s grep\n", argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "grep") == 0)
        grepPlus(argc, argv);

    return 0;
}
