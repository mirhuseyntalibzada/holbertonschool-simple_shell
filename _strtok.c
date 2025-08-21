#include "shell.h"

/**
 * _strtok - Breaks a string into a sequence of tokens.
 * @str: The string to be tokenized. On the first call, this should be the
 * string to parse. On subsequent calls, it should be NULL to continue
 * tokenizing the same string.
 * @delim: A string containing the delimiter characters.
 *
 * Return: A pointer to the next token found in the string,
 * or NULL if no more tokens are found.
 */

char *_strtok(char *str, const char *delim)
{
	static char *saved;
	char *token;
	
	if (str != NULL)
		saved = str;

	if (saved == NULL)
		return (NULL);

	while (*saved && strchr(delim, *saved))
		saved++;

	if (*saved == '\0')
	{
		saved = NULL;
		return (NULL);
	}

	token = saved;

	while (*saved && !strchr(delim, *saved))
		saved++;

	if (*saved)
	{
		*saved = '\0';
		saved++;
	}
	else
	{
		saved = NULL;
	}

	return (token);
}

