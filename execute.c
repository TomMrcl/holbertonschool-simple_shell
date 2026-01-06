#include "main.h"

/**
 * execute_command - Executes a command
 * @command: The command to execute
 * @argv0: Program name for error messages
 * @cmd_number: Command number for error messages
 *
 * Return: void
 */
void execute_command(char *command, char *argv0, int cmd_number)
{
	pid_t pid;
	int status;
	char **args;

	if (command == NULL || strlen(command) == 0)
		return;

	/* Trim whitespace */
	command = trim_whitespace(command);

	if (strlen(command) == 0)
		return;

	/* Parse command into arguments */
	args = parse_command(command);
	if (args == NULL || args[0] == NULL)
	{
		free_array(args);
		return;
	}

	/* Handle built-in exit command */
	if (strcmp(args[0], "exit") == 0)
	{
		free_array(args);
		exit(0);
	}

	/* Check if command is executable */
	if (!is_executable(args[0]))
	{
		print_error(argv0, cmd_number, args[0]);
		free_array(args);
		return;
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free_array(args);
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
		{
			perror(argv0);
			free_array(args);
			exit(1);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
		free_array(args);
	}
}