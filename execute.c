#include "main.h"

/**
 * execute_command - Executes a command
 * @command: The command to execute
 * @argv0: Program name for error messages
 *
 * Return: void
 */
void execute_command(char *command, char *argv0)
{
	pid_t pid;
	int status;
	char *args[2];
	static int cmd_number = 1;

	if (command == NULL || strlen(command) == 0)
		return;

	/* Handle built-in exit command */
	if (strcmp(command, "exit") == 0)
		exit(0);

	/* Check if command is executable */
	if (!is_executable(command))
	{
		print_error(argv0, cmd_number, command);
		cmd_number++;
		return;
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, environ) == -1)
		{
			perror(argv0);
			exit(1);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
		cmd_number++;
	}
}