#include "main.h"

/**
 * free_array - Frees an array of strings
 * @array: Array to free
 *
 * Return: void
 */
void free_array(char **array)
{
	int i;

	if (array == NULL)
		return;

	for (i = 0; array[i] != NULL; i++)
		free(array[i]);

	free(array);
}

/**
 * parse_command - Parses a command string into arguments
 * @command: Command string to parse
 *
 * Return: Array of argument strings, NULL on failure
 */
char **parse_command(char *command)
{
	char **args;
	char *token, *cmd_copy1, *cmd_copy2;
	int count = 0, i = 0;

	if (command == NULL)
		return (NULL);

	cmd_copy1 = strdup(command);
	if (cmd_copy1 == NULL)
		return (NULL);

	token = strtok(cmd_copy1, " \t\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(cmd_copy1);

	if (count == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (NULL);

	cmd_copy2 = strdup(command);
	if (cmd_copy2 == NULL)
	{
		free(args);
		return (NULL);
	}

	token = strtok(cmd_copy2, " \t\n");
	while (token != NULL)
	{
		args[i] = strdup(token);
		if (args[i] == NULL)
		{
			free(cmd_copy2);
			free_array(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	free(cmd_copy2);
	return (args);
}
