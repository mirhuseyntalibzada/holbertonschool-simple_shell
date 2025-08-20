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
