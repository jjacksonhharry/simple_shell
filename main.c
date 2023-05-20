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
	char *arguments[MAX_ARGUMENTS], command[MAX_COMMAND_LENGTH], *buff = NULL;
	int commandExists = 0, exitStatus;
	size_t buf_size = 0;

	if (argc != 1)
		return (1);

	/* loop until user enters 'exit' */
	while (1)
	{
		printf(":) ");

		/* get the user's command */
		if (getline(&buff, &buf_size, stdin) == -1)
		{
			free(buff);
			exit(95);
		}

		/* remove the newline character */
		command[strcspn(buff, "\n")] = '\0';
		/* initialize an array of pointers */
		init_ptrs(arguments, buff);

		/* check if command is exit */
		if (strcmp(arguments[0], "exit") == 0)
		{
			break;
		}
		/* check if command exists */
		commandExists = check_command(arguments[0]);

		/* if it exists execute it */
		if (commandExists)
		{
			exitStatus = executeCommand(arguments, envp);
			printf("%d\n", exitStatus);

			if (exitStatus == -1)
			{
				fprintf(stderr, "%s: No such file exists\n", argv[0]);
			}
		}
		else
		{
			fprintf(stderr, "%s: Command not found\n", command);
		}
	}
	free(buff);
	return (0);
}
