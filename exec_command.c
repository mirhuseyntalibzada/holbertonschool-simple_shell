#include "shell.h"

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
