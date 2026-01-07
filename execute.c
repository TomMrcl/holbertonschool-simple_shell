#include "main.h"

void execute_command(char *command, char *argv0, int cmd_number, char **envp)
{
	pid_t pid;
	int status;
	char **args;
	char *full_path = NULL;
	int free_path = 0;

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

	/* Resolve command */
	if (strchr(args[0], '/') != NULL)
	{
		full_path = args[0];
	}
	else
	{
		full_path = find_command_in_path(args[0], envp);
		free_path = 1;
	}

	/* If not found -> NO FORK */
	if (full_path == NULL || !is_executable(full_path))
	{
		print_error(argv0, cmd_number, args[0]);
		if (free_path && full_path != NULL)
			free(full_path);
		free_array(args);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (free_path)
			free(full_path);
		free_array(args);
		return;
	}

	if (pid == 0)
	{
		if (execve(full_path, args, envp) == -1)
		{
			print_error(argv0, cmd_number, args[0]);
			if (free_path)
				free(full_path);
			free_array(args);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (free_path)
			free(full_path);
		free_array(args);
	}
}
