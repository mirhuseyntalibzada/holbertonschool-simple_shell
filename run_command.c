#include "shell.h"

/**
 * run_command - Decide command path and run it.
 * @cmd: user-typed command (string).
 *
 * Return: status code, -1 if exit built-in, 127 if not found.
 */
int run_command(const char *cmd)
{
        int status = 0;
        char *path = NULL;
        int use_free = 0;
        char **argv = NULL;

        if (!cmd || is_blank(cmd))
                return (0);

        if (strcmp(cmd, "exit") == 0)
                return (-1);

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
                        /* Exact format the checker wants */
                        dprintf(STDERR_FILENO, "%s: %d: %s: not found\n",
                                g_progname, g_cmd_count, argv[0]);
                        free_argv(argv);
                        return (127);
                }
                use_free = 1;
        }

        status = exec_command(path, argv);

        if (use_free)
                free(path);
        free_argv(argv);

        return (status);
}
