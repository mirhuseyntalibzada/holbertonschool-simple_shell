#include "shell.h"

/**
 * contains_slash - Check if command contains '/' (absolute/relative path).
 * @s: command string
 * Return: 1 if contains '/', 0 otherwise
 */
int contains_slash(const char *s)
{
	const char *p = s;

	if (!s)
		return (0);
	while (*p)
	{
		if (*p == '/')
			return (1);
		p++;
	}
	return (0);
}
