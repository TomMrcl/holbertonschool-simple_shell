#include "main.h"

extern char **environ;

/**
 * get_path_env - Gets the PATH environment variable
 *
 * Return: Pointer to PATH string, or NULL if not found
 */
char *get_path_env(void)
{
	int i;

	if (environ == NULL)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}

	return (NULL);
}

/**
 * find_command_in_path - Searches for a command in PATH directories
 * @command: Command to find
 *
 * Return: Full path to command if found, NULL otherwise
 */
char *find_command_in_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	if (command == NULL)
		return (NULL);

	path_env = get_path_env();
	if (path_env == NULL || strlen(path_env) == 0)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		if (strlen(dir) == 0)
		{
			dir = strtok(NULL, ":");
			continue;
		}

		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (is_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
