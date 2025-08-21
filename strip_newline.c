#include "shell.h"

/**
 * strip_newline - Replace trailing '\n' with '\0' in-place.
 * @s: input string (from getline)
 */
void strip_newline(char *s)
{
	size_t n;

	if (!s)
		return;
	n = strlen(s);
	if (n && s[n - 1] == '\n')
		s[n - 1] = '\0';
}
