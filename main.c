#include "shell.h"

void exec_comms(char **arguments, char **envp, int commandExists, char **argv, int *status);

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
	int commandExists = 0, i, stat = EXIT_SUCCESS;
	size_t buf_size = 0;
	char commandPath[MAX_COMMAND_LENGTH];

	if (argc != 1)
		return (1);

	/* loop until user enters 'exit' */
	while (1)
	{
		/* prompt user if in the interactive mode */
		prompt();
		/* get the user's command */
		if (_getline(&buff, &buf_size, stdin) == -1)
		{
			if (feof(stdin))
			{
				free(buff);
				exit(EXIT_SUCCESS);
			}
			else
			{
				free(buff);
				exit(EXIT_SUCCESS);
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
		if (arguments[0] == NULL)
		{
			continue;
		}

		/* check if command is exit */
		if (strcmp(arguments[0], "exit") == 0)
		{
			if (arguments[1] != NULL)
			{
				stat = atoi(arguments[1]);

			}
			free(buff);
			exit(stat);
		}
		/* handle built-in commands */
		if (handle_commands(&arguments[0], envp) == 1)
		{
			continue;
		}
		/* check if command exists */
		commandExists = check_command(arguments[0], commandPath);
		/* if command exists store its path in arguments[0] */
		if (commandExists)
		{
			arguments[0] = strdup(commandPath);
			if (arguments[0] == NULL)
			{
				fprintf(stderr, "Failed to copy to argument\n");
				continue;
			}
		}
		/* execute command if it exists */
		exec_comms(arguments, envp, commandExists, argv, &stat);
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
void exec_comms(char **arguments, char **envp, int commandExists, char **argv, int *status)
{
	int exitStatus;

	/* if it exists execute it */
	if (commandExists)
	{
		exitStatus = executeCommand(arguments, envp);

		if (exitStatus == -1)
		{
			fprintf(stderr, "%s: No such file exists\n", argv[0]);
			*status = 2;
		}
		free(arguments[0]);
	}
	else
	{
		fprintf(stderr, "No such file or directory\n");
		*status = 2;
	}
}
