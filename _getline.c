#include "shell.h"

ssize_t getln(char **lineptr, FILE *stream, size_t *n);
/**
 * _getline - implementation of the getline function
 * @lineptr: where the read text is to be stored
 * @n: size of the buffer that text is to be stored
 * @stream: where the line is to be read from
 *
 * Return: number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	/* if n is 0 give it a random number */
	if (*n == 0)
	{
		*n = 20;
	}
	/* if lineptr is NULL n bytes to it */
	if (*lineptr == NULL)
	{
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
		{
			fprintf(stderr, "Error: Failed to allocate memory");
			return (-1);
		}
	}

	return (getln(lineptr, stream, n));
}

/**
 * getln - loops as it reads the from a stream
 * @lineptr: points to the buffer to store the read text
 * @stream: points to the buffer to be read
 * @n: points to the size of the buffer to be written  into
 *
 * Return: number of characters read
 */

ssize_t getln(char **lineptr, FILE *stream, size_t *n)
{
	size_t i;
	char ch = '\0';

	for (i = 0; ch != '\n'; i++)
	{
		/* read the next character in the stream */
		ch = fgetc(stream);
		if (ch == EOF)
		{
			if (i == 0)
			{
				return (-1);
			}
			break;
		}

		/* check if space is enough */
		if ((i + 1) >= *n)
		{
			/* reallocate more memory if it is not enough */
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				fprintf(stderr, "Failed to reallocate memory");
				return (-1);
			}
		}

		(*lineptr)[i] = ch;
	}
	(*lineptr)[i] = '\0';
	return ((ssize_t) i);
}
