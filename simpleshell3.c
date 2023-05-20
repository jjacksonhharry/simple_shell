#include "shell.h"

/**
 * check_command - checks if command exists
 * @command: the command to be checked
 *
 * Return: 1 on success 0 if failed
 */
int check_command(char *command)
{
	char *path = getenv("PATH");
	char *token, * pathCopy;
	char commandPath[MAX_COMMAND_LENGTH + 1];
	int len;

	if (command == NULL)
	{
		return (0);
	}

	/* check if command is abolute path */
	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			return (1);
		}
	}

	pathCopy = strdup(path);
	if (pathCopy == NULL)
	{
		return (0);
	}

	token = strtok(pathCopy, ":");

	while (token != NULL)
	{
		/* get path to the command */
		len = snprintf(commandPath, sizeof(commandPath), "%s/%s", token, command);

		if (len >= (int)sizeof(commandPath))
		{
			free(pathCopy);
			fprintf(stderr, "commmand is too long: %s\n", command);
			return (0);
		}
		if (access(commandPath, X_OK) == 0)
		{
			/* copy the full path */
			strcpy(command, commandPath);
			free(pathCopy);
			return (1);
		}
		token = strtok(NULL, ":");
	}
	free(pathCopy);
	return (0);
}

/**
 * executecommand - function to execute command
 * @arg_ptr : an array of pointers
 * @envp: environment variablei
 * @argv: command line arguments
 */
int executeCommand(char **arguments, char **envp)
{
	int status;
	pid_t pid;

	/* checks if fork() failed to create a child process */
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	/* This condition checks if the current process is the child process */
	else if (pid == 0)
	{
		printf("%s\n", arguments[0]);
		if (execve(arguments[0], arguments, envp) == -1)
		{
			perror("execve");
			return (-1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (-1);
}
