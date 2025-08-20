#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

#define PROMPT "$ "

/* ===================== Prototypes ===================== */
void print_prompt(void);
void strip_newline(char *s);
int is_blank(const char *s);
int contains_slash(const char *s);
char *build_bin_path(const char *cmd);
int run_command(const char *cmd);

#endif
