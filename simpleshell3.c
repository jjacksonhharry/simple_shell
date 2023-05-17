#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
/**
 * pass_arguments - function that pass a a command
 * string into individual arguments
 * @command: users command
 * @arguments: arguments passed
 * Return: always 0 on success
 */
int pass_arguments(char *command, char **arguments)
{
	int n;	/* n = count to keep track of the number of arguments parsed */
	char *token = strtok(command, " \t\n");

	n = 0;

	while (token != NULL)
	{
		arguments[n] = token;
		n++;
		token = strtok(NULL, " \t\n"); /* strtok function to tokenize the command string */
					/* delimiter is set to " \t\n" which includes space, tab, and newline characters */
		if (n >= MAX_ARGUMENTS - 1)
			break;
	}
	arguments[n] = NULL;

	return (n);
}
/**
 * exec_command - function to execute command
 * @arg_ptr : an array of pointers
 * @envp: environment variablei
 * @argv: command line arguments
 */
int executeCommand(char **arguments)
{
	int status;
	pid_t pid;

	/* checks if fork() failed to create a child process */
	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return -1;
	}
	/* This condition checks if the current process is the child process */
	else if (pid == 0)
	{
		execvp(arguments[0], arguments);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}
/**
 * main - program entry point
 * Return: void
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	char *path = strdup(getenv("PATH"));
	char *pathCopy = strdup(path);
	int commandExists = 0;
	char *token = strtok(path, ":");
	int exitStatus;

	if (pathCopy == NULL)
	{
		perror("strdup");
		return 1;
	}
	printf(":) ");

	while (fgets(command, sizeof(command), stdin))
	{
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		else if (strlen(command) == 0)
			{
				printf(":) ");
				continue;
			}

		while (token!= NULL)
		{
			char commandPath[MAX_COMMAND_LENGTH + 1];
			int len = snprintf(commandPath, sizeof(commandPath), "%s/%s", token, command);

			if (len >= (int)sizeof(commandPath))
			{
				fprintf(stderr, "Command path is too long: %s\n", command);
				break;
			}
		if (access(commandPath, X_OK) == 0)
		{
			commandExists = 1;
			break;
		}
		token = strtok(NULL, ":");
		}
		if (commandExists)
		{
			pass_arguments(command, arguments);
			exitStatus = executeCommand(arguments);

			if ((exitStatus == -1))
			{
			fprintf(stderr, "Failed to execute command: %s\n", command);
			}
		}
			else
			{
				fprintf(stderr, "Command not found: %s\n", command);
			}
			printf(":) ");
	}
		free(pathCopy);
		return (0);
}
