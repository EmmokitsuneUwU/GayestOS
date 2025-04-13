#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP
#define MAX_ARGS 5

extern void proccessCommand(char *args[MAX_ARGS],int argc);
extern void parse_command(char *input, char *args[], int *argc);

#endif // COMMANDPROCESSOR_HPP