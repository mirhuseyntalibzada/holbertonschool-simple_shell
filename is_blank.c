#include "shell.h"

/**
 * is_blank - Check if string is empty or only whitespace.
 * @s: string
 *
 * Return: 1 if blank, 0 otherwise.
 */
int is_blank(const char *s)
{
	const char *p = s;

	if (!s)
		return (1);
	while (*p)
	{
		if (*p != ' ' && *p != '\t' && *p != '\r')
			return (0);
		p++;
	}
	return (1);
}
