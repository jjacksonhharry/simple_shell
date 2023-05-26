#include "shell.h"

/**
 * changeDir - changes directories
 * @commands: an array of pointers holding commands
 *
 * Return: 1 on success and 0 on failure
 */
int changeDir(char **commands)
{
	char *path;
	int status;

	/* if no argument is given to cd go $HOME */
	if (commands[1] == NULL)
	{
		path = getenv("HOME");
		chdir(path);
		return (1);
	}

	/* if there is a directory we change into it */
	status = chdir(commands[1]);
	if (status == -1)
	{
		fprintf(stderr, "%s: could not find directory\n", commands[1]);
		return (0);
	}
	return (1);
}
