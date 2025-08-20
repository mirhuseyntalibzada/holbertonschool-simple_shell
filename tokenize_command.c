#include "shell.h"

/**
 * tokenize_command - split a command string into argv array
 * @cmd: command string
 *
 * Return: NULL-terminated array of strings or NULL on failure
 */
char **tokenize_command(const char *cmd)
{
	char **argv;
	char *token, *copy;
	size_t count = 0, i = 0;

	if (!cmd)
		return (NULL);

	copy = strdup(cmd);
	if (!copy)
		return (NULL);

	token = strtok(copy, " \t\n");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	free(copy);

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);

	copy = strdup(cmd);
	if (!copy)
		return (NULL);

	token = strtok(copy, " \t\n");
	while (token)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			free_argv(argv);
			free(copy);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;
	free(copy);

	return (argv);
}
