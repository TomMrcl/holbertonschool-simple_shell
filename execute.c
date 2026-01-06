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
	char *full_path = NULL;
	int should_free_path = 0;

	if (command == NULL || strlen(command) == 0)
		return;

	command = trim_whitespace(command);
	if (strlen(command) == 0)
		return;

	args = parse_command(command);
	if (args == NULL || args[0] == NULL)
	{
		free_array(args);
		return;
	}

	if (strcmp(args[0], "exit") == 0)
	{
		free_array(args);
		exit(0);
	}

	/* Find command */
	if (strchr(args[0], '/') != NULL)
	{
		/* Command contains '/', treat as path */
		full_path = args[0];
	}
	else
	{
		/* Search in PATH */
		full_path = find_command_in_path(args[0]);
		should_free_path = 1;
	}

	/* Check if command exists and is executable */
	if (full_path == NULL || !is_executable(full_path))
	{
		print_error(argv0, cmd_number, args[0]);
		if (should_free_path && full_path != NULL)
			free(full_path);
		free_array(args);
		return;
	}

	/* Now we can fork */
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		if (should_free_path)
			free(full_path);
		free_array(args);
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(full_path, args, environ) == -1)
		{
			perror(argv0);
			if (should_free_path)
				free(full_path);
			free_array(args);
			exit(1);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
		if (should_free_path)
			free(full_path);
		free_array(args);
	}
}