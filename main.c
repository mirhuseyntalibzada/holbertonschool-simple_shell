#include "shell.h"

/**
 * main - Entry point for the simple shell.
 *
 * Return: process exit status.
 */

int main(void)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t nread;
	int last_status = 0;
	char *cmd;
	int run_status;

	while (1)
	{
		print_prompt();
		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		strip_newline(line);
		cmd = trim_spaces(line);

		if (!is_blank(cmd))
		{
			run_status = run_command(cmd);
			if (run_status == -1)
				break;
			last_status = run_status;
		}
	}

	free(line);
	return (last_status);
}
