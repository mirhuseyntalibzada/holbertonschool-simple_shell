#include "shell.h"

/**
 * build_bin_path - Allocate a new string "/bin/" + cmd.
 * @cmd: command name (no '/')
 * Return: malloc'd path or NULL on failure.
 */
char *build_bin_path(const char *cmd)
{
	char *path_env, *dir, *full_path;
	size_t len;

	if (!cmd)
		return NULL;

	path_env = _getenv("PATH");
	if (!path_env || *path_env == '\0')
		return NULL;

	path_env = strdup(path_env);
	if (!path_env)
		return NULL;

	dir = _strtok(path_env, ":");
	while (dir)
	{
		len = strlen(dir) + 1 + strlen(cmd) + 1;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_env);
			return NULL;
		}
		snprintf(full_path, len, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_env);
			return full_path;
		}
		free(full_path);
		dir = _strtok(NULL, ":");
	}

	free(path_env);
	return NULL;
}
