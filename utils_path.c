#include "main.h"

/**
 * build_full_path - Build "dir/command"
 * @dir: directory
 * @command: command name
 *
 * Return: malloc'ed full path, or NULL
 */
static char *build_full_path(char *dir, char *command)
{
	char *full_path;
	size_t len;

	if (dir == NULL || command == NULL)
		return (NULL);

	len = strlen(dir) + strlen(command) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, command);
	return (full_path);
}

/**
 * try_dir - Try to find command in a single directory
 * @dir: directory to try
 * @command: command name
 *
 * Return: malloc'ed full path if executable, NULL otherwise
 */
static char *try_dir(char *dir, char *command)
{
	char *full_path;

	if (dir == NULL || command == NULL)
		return (NULL);

	if (dir[0] == '\0')
		dir = ".";

	full_path = build_full_path(dir, command);
	if (full_path == NULL)
		return (NULL);

	if (is_executable(full_path))
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
 * find_command_in_path - Search command in PATH directories
 * @command: command name (no '/')
 * @envp: environment
 *
 * Return: malloc'ed full path if found, NULL otherwise
 */
char *find_command_in_path(char *command, char **envp)
{
	char *path_env, *path_copy, *dir, *found;

	if (command == NULL)
		return (NULL);

	path_env = get_env_value(envp, "PATH");
	if (path_env == NULL || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		found = try_dir(dir, command);
		if (found != NULL)
		{
			free(path_copy);
			return (found);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
