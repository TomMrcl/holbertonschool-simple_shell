#include "main.h"

/**
 * get_env_value - Get the value of an environment variable
 * @envp: environment variables array
 * @name: variable name to search (e.g. "PATH")
 *
 * Return: pointer to the value inside envp, or NULL if not found
 */

char *get_env_value(char **envp, const char *name)
{
	size_t nlen;
	int i;

	if (envp == NULL || name == NULL)
		return (NULL);

	nlen = strlen(name);

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], name, nlen) == 0 && envp[i][nlen] == '=')
			return (envp[i] + nlen + 1);
	}
	return (NULL);
}
