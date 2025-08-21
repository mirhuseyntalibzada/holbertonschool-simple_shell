#include "shell.h"

/**
 * run_command - Decide command path and run it.
 * @cmd: user-typed command (one word)
 *
 * Return: status code.
 */

int run_command(const char *cmd)
{
	int status = 0;
	char *path = NULL;
	int use_free = 0;
	char **argv = NULL;

	if (!cmd || is_blank(cmd))
		return 0;

	if (strcmp(cmd, "exit") == 0)
		return -1;

	argv = tokenize_command(cmd);
	if (!argv || !argv[0])
	{
		free_argv(argv);
		return 0;
	}

	if (contains_slash(argv[0]))
	{
		path = argv[0];
	}
	else
	{
		path = build_bin_path(argv[0]);
		if (!path)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
			free_argv(argv);
			return 1;
		}
		use_free = 1;
	}

	status = exec_command(path, argv);

	if (use_free)
		free(path);
	free_argv(argv);

	return status;
}
