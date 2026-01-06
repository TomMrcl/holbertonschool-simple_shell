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

/* Fonctions principales */
void display_prompt(void);
char *read_line(void);
int execute_command(char *command, char *argv0);
void print_error(char *argv0, int cmd_count, char *command);

#endif /* MAIN_H */