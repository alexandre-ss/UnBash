#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 32

#ifndef STACK
#define STACK
char history[11][32];
const int MAXSIZE = 10;
int top = -1;
#endif

void execute(char *);
void parse_command(char *, size_t);
void name_and_current_directory(char *, char *);
char* read_command_line(char *, size_t);
void history_stack(char *);
void history_show(char *);
void execute_with_args(char **);
void separate_args(char *, char **);
void execute_pipe(char **, char **);
int is_background(char *);
void execute_background_cmd(char *);