#include "shell.h"

int getPath(char *command, char *pathCopy, char *commandPath);
/**
 * check_command - checks if command exists
 * @command: the command to be checked
 *
 * Return: 1 on success 0 if failed
 */
int check_command(char *command)
{
	char *path = getenv("PATH");
	char commandPath[MAX_COMMAND_LENGTH] = " ";
	char *pathCopy;
	int commExists;

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

	commExists = getPath(command, pathCopy, commandPath);

	free(pathCopy);
	return (commExists);
}

/**
 * getPath - gets the path of a command and checks if valid
 * @command: contains the users command
 * @pathCopy: contains a copy from PATH
 * @commandPath: the path of the command
 * Return: 1 if succesful and 0 if failed
 */
int getPath(char *command, char *pathCopy, char *commandPath)
{
	char *token;
	int len;

	token = _strtok(pathCopy, ":");

	while (token != NULL)
	{
		/* get path to the command */
		len = snprintf(commandPath, MAX_COMMAND_LENGTH, "%s/%s", token, command);

		if (len >= MAX_COMMAND_LENGTH)
		{
			fprintf(stderr, "commmand is too long: %s\n", command);
			return (0);
		}
		if (access(commandPath, X_OK) == 0)
		{
			/* copy the full path */
			strcpy(command, commandPath);
			return (1);
		}
		token = _strtok(NULL, ":");
	}
	return (0);
}

/**
 * executeCommand - function to execute command
 * @arguments : an array of pointers
 * @envp: environment variablei
 *
 * Return: -1 if failed
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
		return (-1);
	}
	/* This condition checks if the current process is the child process */
	else if (pid == 0)
	{
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


/**
 * handle_commands - Function that handles built commands
 * @command: command to be checked
 * @environ: environment to be printed
 * Return: 0 else 1 on success
 */
int handle_commands(char **command, char **environ)
{
	if (strcmp(command[0], "env") == 0)
	{
		print_environment(environ);
		return (1);
	}
	else if (strcmp(command[0], "cd") == 0)
	{
		changeDir(command);
		return (1);
	}
	else if (strcmp(command[0], "setenv") == 0)
	{
		return (setenviron(command));
	}
	else
	{
		return (0);
	}
}

/**
 * print_environment - Function that prints environment
 * @environ: environment to be printed
 */
void print_environment(char **environ)
{
	int i;

	i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
