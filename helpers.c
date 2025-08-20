#include "shell.h"

#define PROMPT "$ "

/* ===================== Helpers ===================== */
/**
 * print_prompt - Print shell prompt when in interactive mode.
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, PROMPT, (unsigned int)strlen(PROMPT));
}

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
