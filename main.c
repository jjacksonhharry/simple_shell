#include "shell.h"

void free_ptr(char *array_ptr[]);
void exec_comms(char **arguments, char **envp, int commandExists, char **argv);

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
	char *arguments[MAX_ARGUMENTS], *buff = NULL;
	int commandExists = 0, i;
	size_t buf_size = 0;

	if (argc != 1)
		return (1);

	/* loop until user enters 'exit' */
	while (1)
	{
		prompt();

		/* get the user's command */
		if (_getline(&buff, &buf_size, stdin) == -1)
		{
			if (feof(stdin))
			{
				write(1, "\n", 2);
				break;
			}
			else
			{
				free(buff);
				exit(1);
			}
		}

		/* remove the newline character */
		i = 0;
		while (buff)
		{
			if (buff[i] == '\n')
			{
				buff[i] = '\0';
				break;
			}
			i++;
		}
		/* initialize an array of pointers */
		init_ptrs(arguments, buff);

		/* check if command is exit */
		if (strcmp(arguments[0], "exit") == 0)
		{
			break;
		}
		/* check if command exists */
		commandExists = check_command(arguments[0]);

		exec_comms(arguments, envp, commandExists, argv);
	}
	free_ptr(arguments);
	free(buff);
	return (0);
}

/**
 * exec_comms - check if command exists and execute it
 * @arguments: array of pointers
 * @envp: environment variable
 * @commandExists: the status of the command
 * @argv: argument vector
 */
void exec_comms(char **arguments, char **envp, int commandExists, char **argv)
{
	int exitStatus;

	/* if it exists execute it */
	if (commandExists)
	{
		exitStatus = executeCommand(arguments, envp);

		if (exitStatus == -1)
		{
			fprintf(stderr, "%s: No such file exists\n", argv[0]);
		}
	}
	else
	{
		fprintf(stderr, "Command not found\n");
	}
}
/**
 * free_ptr - loops through the array of pointers freeing each memory
 * @array_ptr: the array pointer
 */
void free_ptr(char *array_ptr[])
{
	int i;

	for (i = 0; array_ptr[i] != NULL; i++)
	{
		free(array_ptr[i]);
	}
}
