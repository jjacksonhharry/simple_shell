#include "shell.h"

char *trtok(char *str, const char *delim)
{
    static char *backup = NULL;
    char *token;

    if (str != NULL)
        backup = str;

    if (backup == NULL)
        return NULL;

    /* Skip leading delimiters */
    while (*backup != '\0' && strchr(delim, *backup) != NULL)
        backup++;

    if (*backup == '\0')
    {
        backup = NULL;
        return NULL;
    }

    token = backup;

    /* Find the end of the token */
    while (*backup != '\0' && strchr(delim, *backup) == NULL)
        backup++;

    if (*backup != '\0')
    {
        *backup = '\0';
        backup++;
    }

    return token;
}

