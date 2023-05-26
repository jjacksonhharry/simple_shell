#include "shell.h"
#include <unistd.h>

/**
 * exit_shell - exitshell
 */
void exit_shell(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * handle_commands - Function that handles built commands
 * @command: command to be checked
 * @environ: environment to be printed
 * Return: 0 else 1 on success
 */
int handle_commands(char *command, char **environ)
{
	if (strcmp(command, "exit") == 0)
	{
		exit_shell();
		return (1);
	}
	else if (strcmp(command, "env") == 0)
	{
		print_environment(environ);
		return (1);
	}
	return (0);
}

/**
 * print_environment - Function that prints environment
 * @environ: environment to be printed
 */
void print_environment(char **environ)
{
	int i;

	i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
