#include "shell.h"

/**
 * prompt - prompts the user for input
 */
void prompt(void)
{
	if (isatty(STDOUT_FILENO))
	{
		printf(":) ");
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

	arg_ptr[i] = strtok(buff, " \t\n");

	while (arg_ptr[i] != NULL)
	{
		i++;
		arg_ptr[i] = strtok(NULL, " \t\n");
	}
}
