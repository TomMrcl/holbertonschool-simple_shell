#include "main.h"

char *find_command_in_path(char *command, char **envp)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

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
		/* empty entry = current directory */
		if (dir[0] == '\0')
			dir = ".";

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
