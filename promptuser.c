#include "shell.h"
/**
 * promptuser - function that prompts the user
 */
void promptuser(char **envp)
{
	int status, i;
	char *buff = NULL, *av[20];
	size_t buf_size = 0;
	pid_t pid;

	/* start an infinite loop for the prompt */
	while (1)
	{
		/* print the prompt */
		printf("#cisfun$ ");
		fflush(stdout);
		/* get the line printed in the std input */
		if (getline(&buff, &buf_size, stdin) == -1)
		{
			/* if getting line is successful exit */
			free(buff);
			exit(1);
		}
		/* replace new line with null terminator */
		for (i = 0; buff[i] != '\0'; i++)
		{
			if (buff[i] == '\n')
				buff[i] = '\0';
		}
		/* initialize array of pointers */
		av[0] = buff;
		av[1] = NULL;
		/* start child process */
		pid = fork();
		if (pid == -1)
		{
			free(buff);
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(av[0], av, envp) == -1)
			{
				printf("Error: command not found\n");
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}
}
