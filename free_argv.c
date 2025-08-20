#include "shell.h"

/**
 * free_argv - free a NULL-terminated argv array
 * @argv: array of strings
 */
void free_argv(char **argv)
{
	size_t i;

	if (!argv)
		return;

	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
}
