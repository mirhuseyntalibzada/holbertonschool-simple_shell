#include "shell.h"

/**
 * build_bin_path - Allocate a new string "/bin/" + cmd.
 * @cmd: command name (no '/')
 * Return: malloc'd path or NULL on failure.
 */
char *build_bin_path(const char *cmd)
{
	char *path;
	size_t len_bin = 5; /* strlen("/bin/") */
	size_t len_cmd;

	if (!cmd)
		return (NULL);
	len_cmd = strlen(cmd);
	path = malloc(len_bin + len_cmd + 1);
	if (!path)
		return (NULL);
	strcpy(path, "/bin/");
	strcpy(path + len_bin, cmd);
	return (path);
}

/**
 * exec_command - Execute a command in a child process.
 * @path: full path to the executable
 * @cmd: original command name
 *
 * Return: child exit status.
 */
int exec_command(char *path, char *const argv[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			_exit(1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
	}
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

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
		return (0);

	argv = tokenize_command(cmd);
	if (!argv || !argv[0])
	{
		free_argv(argv);
		return (0);
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
			perror("malloc");
			free_argv(argv);
			return (1);
		}
		use_free = 1;
	}

	status = exec_command(path, argv);

	if (use_free)
		free(path);
	free_argv(argv);

	return (status);
}
