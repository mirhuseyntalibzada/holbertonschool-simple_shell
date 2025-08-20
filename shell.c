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
int exec_command(char *path, const char *cmd)
{
	pid_t pid;
	int status = 0;
	char *argv[2];

	argv[0] = (char *)cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execve(path, argv, environ);
		perror("execve");
		_exit(127);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
	}
	return (status);
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

	if (!cmd || is_blank(cmd))
		return (0);

	if (contains_slash(cmd))
	{
		path = (char *)cmd;
	}
	else
	{
		path = build_bin_path(cmd);
		if (!path)
		{
			perror("malloc");
			return (1);
		}
		use_free = 1;
	}

	status = exec_command(path, cmd);

	if (use_free)
		free(path);

	return (status);
}
