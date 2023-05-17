#include "shell.h"


void exec_command(char *arg_ptr[], char **argv, char **envp);
void init_ptrs(char *arg_ptr[], char *buff);

/**
 * init_ptrs - function to separate string based on spaces
 * @arg_ptr: array of pointers
 * @buff: input string
 */
void init_ptrs(char *arg_ptr[], char *buff)
{
	int i = 0;

	arg_ptr[i] = strtok(buff, " ");

	while (arg_ptr[i] != NULL)
	{
		i++;
		arg_ptr[i] = strtok(NULL, " ");
	}
}

/**
 * promptuser - function that prompts the user
 * @envp: environment variable
 * @argv: command line arguments
 */
void promptuser(char **argv, char **envp)
{
	int i;
	char *buff = NULL, *arg_ptr[20];
	size_t buf_size = 0;

	/* start an infinite loop for the prompt */
	while (1)
	{
		/* display the prompt */
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
		init_ptrs(arg_ptr, buff);

		/* call a function to execute commands */
		exec_command(arg_ptr, argv, envp);
	}
	free(buff);
}

/**
 * exec_command - function to execute command
 * @arg_ptr : an array of pointers
 * @envp: environment variablei
 * @argv: command line arguments
 */
void exec_command(char *arg_ptr[], char **argv, char **envp)
{
	int status;
	pid_t pid;

	/* create child process */
	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(arg_ptr[0], arg_ptr, envp) == -1)
		{
			printf("%s: No such file or directory\n", argv[0]);
			exit(1);
		}
	}
	else
	{
		/* wait for the child process to execute */
		wait(&status);
	}
}
