#include "shell.h"

int delCheck(char *delim, char c);
/**
 * _strtok - breaks a string into a series of tokens
 * @str: the cstring containg the content to be modified
 * @delim: string containing the delimeters
 *
 * Return: pointer to the first token found in the string
 */
char *_strtok(char *str, char *delim)
{
	static char *backup;/*to store the remaining string */
	int i, j;
	char *newString = NULL;

	if (str == NULL)
		str = backup;
	if (str == NULL)
		return (NULL);
	newString = malloc(strlen(str) + 1);
	if (newString == NULL)
	{
		free(backup);
		return (NULL);
	}

	/* loop through each character */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (delCheck(delim, str[i]))
		{
			i++;
			break;
		}
		else
		{
			newString[i] = str[i];
		}
	}
	newString[i] = '\0';
	if (str[i] == '\0')
	{
		free(backup);
		backup = NULL;
	}
	else
	{
		if (backup == NULL)
			backup = malloc(strlen(str) + 1);
		if (backup == NULL)
		{
			free(newString);
			return (NULL);
		}
		for (j = 0; str[i] != '\0'; i++)
		{
			backup[j] = str[i];
			j++;
		}
		backup[j] = '\0';
	}
	return (newString);
}

/**
 * delCheck - checks if a character is a delimeter
 * @delim: the delimeter
 * @c: character to be checked
 *
 * Return: 1 on success 0 if not
 */
int delCheck(char *delim, char c)
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (c == delim[i])
			return (1);
	}
	return (0);
}
