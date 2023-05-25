#include "shell.h"

/**
 * _strtok - breaks a string into a series of tokens
 * @str: the cstring containg the content to be modified
 * @delim: string containing the delimeters
 *
 * Return: pointer to the first token found in the string
 */
char *_strtok(char *str, char *delim)
{
	static char *backup = NULL;/*to store the remaining string */
	int i, j, delFound = 0;
	char *newString = NULL;

	if (str == NULL)
		str = backup;
	if (str == NULL)
		return (NULL);
	newString = malloc(strlen(str) + 1);
	if (newString == NULL)
		return (NULL);

	/* loop through each character */
	for (i = 0; str[i] != '\0'; i++)
	{
		/* loop through the delimeters */
		for (j = 0; delim[j] != '\0'; j++)
		{
			/* check if we reached a delimeter */
			if (str[i] == delim[j])
			{
				delFound = 1;
				break;
			}
		}
		if (delFound)
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
