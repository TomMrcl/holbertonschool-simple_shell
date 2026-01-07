#include "main.h"

/**
 * handle_builtins - Handle built-in commands
 * @args: tokenized command
 * @envp: environment
 * @last_status: pointer to last status
 * @should_exit: pointer to exit flag
 *
 * Return: 1 if a builtin was handled, 0 otherwise
 */
static int handle_builtins(char **args, char **envp, int *last_status,
			   int *should_exit)
{
	if (strcmp(args[0], "exit") == 0)
	{
		*should_exit = 1;
		return (1);
	}

	if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		*last_status = 0;
		return (1);
	}

	return (0);
}

/**
 * resolve_command_path - Resolve command path (absolute/relative or PATH)
 * @cmd: command name (args[0])
 * @envp: environment
 * @free_path: set to 1 if returned path must be freed
 *
 * Return: resolved path or NULL
 */
static char *resolve_command_path(char *cmd, char **envp, int *free_path)
{
	char *path;

	*free_path = 0;

	if (cmd == NULL)
		return (NULL);

	if (strchr(cmd, '/') != NULL)
		return (cmd);

	path = find_command_in_path(cmd, envp);
	if (path != NULL)
		*free_path = 1;

	return (path);
}

/**
 * run_fork_exec - Fork and exec a command
 * @path: full path to command
 * @args: arguments array
 * @envp: environment
 *
 * Return: exit status
 */
static int run_fork_exec(char *path, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		execve(path, args, envp);
		exit(127);
	}

	wait(&status);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

/**
 * cleanup_exec - Free allocated resources after execution
 * @args: arguments array
 * @path: resolved path (maybe allocated)
 * @free_path: whether path must be freed
 *
 * Return: void
 */
static void cleanup_exec(char **args, char *path, int free_path)
{
	if (free_path && path != NULL)
		free(path);

	free_array(args);
}

/**
 * execute_command - Executes a command
 * @command: raw command line
 * @argv0: program name (for errors)
 * @cmd_number: command counter
 * @envp: environment
 * @last_status: pointer to last status
 * @should_exit: pointer to exit flag
 *
 * Return: void
 */
void execute_command(char *command, char *argv0, int cmd_number,
		     char **envp, int *last_status, int *should_exit)
{
	char **args = NULL;
	char *path = NULL;
	int free_path = 0;

	if (command == NULL || last_status == NULL || should_exit == NULL)
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

	if (handle_builtins(args, envp, last_status, should_exit))
	{
		free_array(args);
		return;
	}

	path = resolve_command_path(args[0], envp, &free_path);

	if (path == NULL || !is_executable(path))
	{
		print_error(argv0, cmd_number, args[0]);
		*last_status = 127;
		cleanup_exec(args, path, free_path);
		return;
	}

	*last_status = run_fork_exec(path, args, envp);
	cleanup_exec(args, path, free_path);
}
