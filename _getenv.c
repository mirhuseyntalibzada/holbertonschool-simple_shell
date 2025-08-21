#include "shell.h"
#include <string.h>
#include <stddef.h>

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable to search for.
 *
 * Return: A pointer to the string containing the value of the variable,
 * or NULL if the environment variable is not found.
 */

char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

