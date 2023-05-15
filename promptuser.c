#include "shell.h"
/**
 * promptuser - function that prompts the user
 */
void promptuser(char **envp)
{
	int status, i;
	char *buff;
	size_t buf_size = 0;
	pid_t pid;
	char *argv[10];

	/* start an infinite loop for the prompt */
	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (getline(&buff, &buf_size, stdin) == -1)
		{
			free(buff);
			exit(1);
		}
		for (i = 0; buff[i] != '\0'; i++)
		{
			if (buff[i] == '\n')
				buff[i] = 0;
		}

		argv[0] = buff;
		argv[1] = "NULL";
		pid = fork();
		if (pid == -1)
		{
			free(buff);
			printf("Error: fork failed\n");
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, envp) == -1)
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
