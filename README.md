# Simple Shell

A simple command line shell implemented in C.

## Features

- Executes commands with arguments
- Supports `exit` built-in to exit the shell
- Supports absolute paths (e.g., `/bin/ls`)
- Handles empty and invalid commands

## Usage

Compile the shell:

```bash
gcc -Wall -Werror -Wextra -pedantic main.c run_command.c build_bin_path.c exec_command.c -o hsh
