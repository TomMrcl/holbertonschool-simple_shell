#include "main.h"

/**
 * is_executable - Checks if a file exists and is executable
 * @path: Path to the file
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (path == NULL)
		return (0);

	if (stat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode) && (access(path, X_OK) == 0))
			return (1);
	}

	return (0);
}

/**
 * print_error - Prints an error message
 * @program_name: Name of the shell program
 * @cmd_number: Command number
 * @command: The command that failed
 *
 * Return: void
 */
void print_error(char *program_name, int cmd_number, char *command)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, cmd_number, command);
	fflush(stderr);
}

/**
 * trim_whitespace - Removes leading and trailing whitespace
 * @str: String to trim
 *
 * Return: Pointer to trimmed string
 */
char *trim_whitespace(char *str)
{
	char *end;
	char *start = str;

	if (str == NULL)
		return (NULL);

	/* Trim leading space */
	while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')
		start++;

	/* All spaces? */
	if (*start == '\0')
	{
		str[0] = '\0';
		return (str);
	}

	/* Trim trailing space */
	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || 
			*end == '\n' || *end == '\r'))
		end--;

	/* Write new null terminator */
	*(end + 1) = '\0';

	/* Move trimmed string to beginning */
	if (start != str)
	{
		char *p = str;
		while (*start)
			*p++ = *start++;
		*p = '\0';
	}

	return (str);
}

/**
 * parse_command - Parses a command string into arguments
 * @command: Command string to parse
 *
 * Return: Array of argument strings, NULL on failure
 */
char **parse_command(char *command)
{
	char **args = NULL;
	char *token, *cmd_copy1, *cmd_copy2;
	int i = 0, count = 0;

	if (command == NULL)
		return (NULL);

	/* Count tokens first */
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

	/* Allocate array */
	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (NULL);

	/* Fill array with second copy */
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