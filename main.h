#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes */
void display_prompt(void);
char *read_command(void);
void execute_command(char *command, char *argv0);
void print_error(char *program_name, int cmd_number, char *command);
int is_executable(char *path);
char *trim_whitespace(char *str);

#endif /* MAIN_H */