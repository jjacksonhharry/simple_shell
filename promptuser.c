#include "shell.h"

/**
 * prompt - prompts the user for input
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, ":) ", 3);
	}
}
/**
 * init_ptrs - function to separate string based on spaces
 * @arg_ptr: array of pointers
 * @buff: input string
 */
void init_ptrs(char *arg_ptr[], char *buff)
{
	int i = 0;
	char *token = _strtok(buff, " \t\n\r");

	while (token != NULL)
	{
		/** handle whitespace */
		if (token[0] == '\0')
		{
			token = _strtok(NULL, " \t\n\r");
			continue;
		}
		arg_ptr[i] = token;
		i++;
		token = _strtok(NULL, " \t\n\r");
	}
	free(token);
	arg_ptr[i] = NULL;
}
