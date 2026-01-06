#include "main.h"

/**
 * main - Entry point for the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	char *command = NULL;
	int cmd_number = 1;
	int interactive = isatty(STDIN_FILENO);

	(void)argc;

	while (1)
	{
		if (interactive)
			display_prompt();

		command = read_command();

		if (command == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (strlen(command) == 0)
		{
			free(command);
			continue;
		}

		execute_command(command, argv[0]);
		free(command);
		cmd_number++;
	}

	return (0);
}