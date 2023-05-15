#include "shell.h"
/**
 * main - function that prompts the user
 * @argc: integer
 * @argv: pointer to character
 * @envp: enviroment
 * Return: Always 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	int status;
	char buff[BUFFER_SIZE];
	pid_t pid;
	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(buff, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		buff[strcspn(buff, "\n")] = '\0';

		pid = fork();
		if (pid == -1)
		{
			printf("Error: fork failed\n");
			exit(1);
		}
		if (pid == 0)
		{
			if (execlp(buff, buff, (char *) NULL) == -1)
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
	return (0);
}
