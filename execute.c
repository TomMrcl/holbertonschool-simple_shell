#include "main.h"

void execute_command(char *command, char *argv0, int cmd_number,
		     char **envp, int *last_status)
{
	pid_t pid;
	int status;
	char **args = NULL;
	char *full_path = NULL;
	int free_path = 0;

	if (command == NULL || last_status == NULL)
		return;

	command = trim_whitespace(command);
	if (command[0] == '\0')
		return;

	args = parse_command(command);
	if (args == NULL || args[0] == NULL)
	{
		free_array(args);
		return;
	}

	/* Built-in: exit */
	if (strcmp(args[0], "exit") == 0)
	{
		free_array(args);
		exit(*last_status);
	}

	/* Resolve path */
	if (strchr(args[0], '/') != NULL)
	{
		full_path = args[0];
	}
	else
	{
		full_path = find_command_in_path(args[0], envp);
		free_path = 1;
	}

	/* If not found: NO FORK + status 127 */
	if (full_path == NULL || !is_executable(full_path))
	{
		print_error(argv0, cmd_number, args[0]);
		*last_status = 127;

		if (free_path && full_path != NULL)
			free(full_path);
		free_array(args);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		*last_status = 1;
		if (free_path)
			free(full_path);
		free_array(args);
		return;
	}

	if (pid == 0)
	{
		execve(full_path, args, envp);
		print_error(argv0, cmd_number, args[0]);
		if (free_path)
			free(full_path);
		free_array(args);
		exit(127);
	}

	wait(&status);

	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else
		*last_status = 1;

	if (free_path)
		free(full_path);
	free_array(args);
}
