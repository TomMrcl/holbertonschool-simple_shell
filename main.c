#include "main.h"

int main(int argc, char **argv, char **envp)
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
			cmd_number++;
			continue;
		}

		execute_command(command, argv[0], cmd_number, envp);
		free(command);
		cmd_number++;
	}

	return (0);
}
