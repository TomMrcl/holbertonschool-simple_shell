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
 * count_tokens - Count tokens in a command string
 * @command: command line
 *
 * Return: number of tokens
 */
static int count_tokens(char *command)
{
	char *copy, *token;
	int count = 0;

	copy = strdup(command);
	if (copy == NULL)
		return (0);

	token = strtok(copy, " \t\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}

	free(copy);
	return (count);
}

/**
 * fill_args - Fill args array from command string
 * @args: array to fill
 * @command: command line
 *
 * Return: 1 on success, 0 on failure
 */
static int fill_args(char **args, char *command)
{
	char *copy, *token;
	int i = 0;

	copy = strdup(command);
	if (copy == NULL)
		return (0);

	token = strtok(copy, " \t\n");
	while (token != NULL)
	{
		args[i] = strdup(token);
		if (args[i] == NULL)
		{
			free(copy);
			free_array(args);
			return (0);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL;
	free(copy);
	return (1);
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
	int count;

	if (command == NULL)
		return (NULL);

	count = count_tokens(command);
	if (count == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (NULL);

	if (!fill_args(args, command))
		return (NULL);

	return (args);
}
