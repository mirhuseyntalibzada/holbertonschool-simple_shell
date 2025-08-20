#include "shell.h"

/**
 * trim_spaces - Trims spaces in each commands.
 *
 * @s: string
 *
 * Return: string
 */

char *trim_spaces(char *s)
{
	char *end;

	while (*s == ' ' || *s == '\t')
		s++;

	if (*s == '\0')
		return (s);

	end = s + strlen(s) - 1;
	while (end > s && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';
	return (s);
}
