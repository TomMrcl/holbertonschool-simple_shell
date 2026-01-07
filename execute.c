#include "main.h"

void execute_command(char *command, char *argv0, int cmd_number, char **envp,
		     int *last_status)
{
	pid_t pid;
	int status;
	char **args;
	char *full_path = NULL;
	int free_path = 0;

	if (last_status == NULL)
		return;

	/* ...trim + parse... */

	/* Resolve */
	if (strchr(args[0], '/') != NULL)
		full_path = args[0];
	else
	{
		full_path = find_command_in_path(args[0], envp);
		free_path = 1;
	}

	/* Not found => NO FORK + exit status 127 */
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
		free_array(args);
		if (free_path)
			free(full_path);
		exit(127);
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else
			*last_status = 1;

		if (free_path)
			free(full_path);
		free_array(args);
	}
}
