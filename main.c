#include "shell.h"

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
	int commandExists = 0;
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
			free(buff);
			exit(95);
		}

		/* remove the newline character */
		buff[strcspn(buff, "\n")] = '\0';
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

