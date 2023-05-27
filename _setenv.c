#include "shell.h"

/**
 * _setenviron - sets the environment variable
 * @commands: a pointer to commands
 * Return 1 on success
 */
int setenviron(char **commands)
{
	if (commands[1] == NULL && commands[2] == NULL)
	{
		fprintf(stderr, "Not enough arguments\n");
		return (0);
	}

	if (setenv(commands[1], commands[2], 1) != 0)
	{
		fprintf(stderr, "Failed to setenv\n");
		return (0);
	}
	return (1);
}
