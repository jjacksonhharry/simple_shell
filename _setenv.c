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

	
	if (commands[2] != NULL)
	{
		if(setenv(commands[1], commands[2], 1) != 0)
		{
			fprintf(stderr, "Failed to setenv\n");
			return (0);
		}
		else
		{
			return (1);
		}

	}
	else
	{
		if (setenv(commands[1], "", 1) != 0)
		{
			fprintf(stderr, "Failed to setenv\n");
			return (0);
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

/**
 * unsetenviron - unset an environment variable
 * @commands: an array of commands
 * Return: 1 on success
 */
int unsetenviron(char **commands)
{
	if (commands[1] == NULL)
	{
		fprintf(stderr, "Nothing to unset\n");
		return (0);
	}

	if (getenv(commands[1]) == NULL)
	{
		fprintf(stderr, "%s: The variable is not found\n", commands[1]);
		return (0);
	}
	else
	{
		unsetenv(commands[1]);
		return (1);
	}
	return (0);
}
