#include "simple_shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * hsh_loop - main shell loop
 *
 * Return: 0 on success
 */
int hsh_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	pid_t pid;
	char *cmd_path;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			return (0);
		}

		trim_spaces(line);
		if (line[0] == '\0')
			continue;

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free_argv(argv);
			continue;
		}

		/* Resolve command path */
		if (strchr(argv[0], '/'))
			cmd_path = argv[0];
		else
			cmd_path = find_path(argv[0]);

		/* Command not found → NO fork */
		if (cmd_path == NULL)
		{
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, argv[0], strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 13);

			free_argv(argv);
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, argv, environ) == -1)
			{
				perror("execve");
				free_argv(argv);
				exit(1);
			}
		}
		else if (pid > 0)
		{
			wait(NULL);
		}

		free_argv(argv);
	}
}

