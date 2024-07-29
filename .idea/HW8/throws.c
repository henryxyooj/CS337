void throwOutOfBoundsTerminalInputs();
void throwInvalidCommand();
void throwInvalidPipe();
void throwInvalidFlag();
void throwPipeError();
void throwProcessError();

void throwOutOfBoundsTerminalInputs() {
    puts("Error: Invalid amount of arguments to the terminal.");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

void throwInvalidCommand() {
    puts("Error: pipe.c currently supports only these two commands: \"wc\" or \"sort\"");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

void throwInvalidPipe() {
    puts("Error: Use the pipe command with either: \"|\" or \'|\'");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

void throwInvalidFlag() {
    puts("Error: pipe.c currently supports only these flags for wc command: [-l], [-w], or [-c]");
    puts("Usage: [./main] [cat] [filename] [\"|\" or \'|\'] [command: wc or sort] [optional flag for wc: -l or -w or -c]");
    exit(1);
}

void throwPipeError() {
    puts("Error piping.");
    exit(1);
}

void throwProcessError() {
    puts("Error creating child process.");
    exit(1);
}