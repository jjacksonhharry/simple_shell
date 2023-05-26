#include "shell.h"

int delCheck(const char *delim, char c);
/**
 * _strtok - breaks a string into a series of tokens
 * @str: the cstring containg the content to be modified
 * @delims: string containing the delimeters
 *
 * Return: pointer to the first token found in the string
 */
char *_strtok(char *str, const char *delims)
{
	static char *strBackup;/*to store the remaining string */
	char *newString;

	if (str != NULL)
		strBackup = str;

	if (strBackup == NULL)
		return (NULL);
	if (*strBackup == '\0')
		return (NULL);

	/* skip leading delimeters */
	while ((*strBackup != '\0') && (delCheck(delims, *strBackup) == 1))
	{
			strBackup++;
	}

	if (*strBackup == '\0')
	{
		strBackup = NULL;
		return (NULL);
	}

	newString = strBackup;

	/* loop through each character */
	while (*strBackup != '\0' && delCheck(delims, *strBackup) == 0)
	{
		strBackup++;
	}
	if (*strBackup != '\0')
	{
		*strBackup = '\0';
		strBackup++;
	}
	return (newString);
}

/**
 * delCheck - checks if a character is a delimeter
 * @delim: the delimeter
 * @c: character to be checked
 *
 * Return: delim found on success NULL if not
 */
int delCheck(const char *delim, char c)
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (delim[i] == c)
			return (1);
	}
	return (0);
}
