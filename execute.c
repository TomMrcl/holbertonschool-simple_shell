#include "main.h"

void execute_command(char *command, char *argv0, int cmd_number, char **envp)
{
	pid_t pid;
	int status;
	char **args;
	char *path;

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

	/* 0.1: no builtins required - if you keep exit, ok, but not required */
	if (strcmp(args[0], "exit") == 0)
	{
		free_array(args);
		exit(0);
	}

	/* 0.1: do NOT use PATH.
	 * If user types "ls", execve("ls", ...) will fail -> print not found.
	 */
	path = args[0];

	if (!is_executable(path))
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
		if (execve(path, args, envp) == -1)
		{
			/* For 0.1, prefer the formatted error over perror */
			print_error(argv0, cmd_number, args[0]);
			free_array(args);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free_array(args);
	}
}
