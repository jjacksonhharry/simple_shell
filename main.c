#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: command line arguments
 * @envp: environment variable
 *
 * Return: 0 Always
 */
int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		promptuser(argv, envp);
	}
	return (0);
}
