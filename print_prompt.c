#include "shell.h"

/**
 * print_prompt - Print shell prompt when in interactive mode.
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, PROMPT, (unsigned int)strlen(PROMPT));
}
