#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

#ifndef VARIABLES
#define VARIABLES
char *history[11];
int history_counter = 0;

#endif


void execute(char *);
void parse_command(char *, size_t);
void name_and_current_directory(char *, char *);
char* read_command_line(char *, size_t);
void history_stack(char *);
void history_show(char *);