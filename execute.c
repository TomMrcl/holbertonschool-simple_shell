#include "main.h"

/**
 * execute_command - Exécute une commande
 * @command: La commande à exécuter
 * @argv0: Nom du programme (pour les erreurs)
 *
 * Return: 0 en cas de succès, -1 en cas d'erreur
 */
 
int execute_command(char *command, char *argv0)
{
	pid_t pid;
	int status;
	char *args[2];
	struct stat st;
	(void)argv0;

	if (stat(command, &st) != 0)
		return (-1);

	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}