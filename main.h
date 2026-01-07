#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* prompt / read */
void display_prompt(void);
char *read_command(void);

/* execute */
void execute_command(char *command, char *argv0, int cmd_number,
		     char **envp, int *last_status, int *should_exit);

/* errors / exec utils */
int is_executable(char *path);
void print_error(char *program_name, int cmd_number, char *command);

/* parsing / strings */
char *trim_whitespace(char *str);
char **parse_command(char *command);
void free_array(char **array);

/* env / path */
char *get_env_value(char **envp, const char *name);
char *find_command_in_path(char *command, char **envp);

#endif
