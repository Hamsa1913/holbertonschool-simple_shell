#include "simple_shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * hsh_loop - main shell execution loop
 *
 * Return: 0 on success
 */
int hsh_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	char *cmd_path;
	pid_t pid;

	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if (read > 1)
		{
			argv = split_line(line);
			if (argv && argv[0])
			{
				/* Resolve command path */
				if (strchr(argv[0], '/'))
					cmd_path = argv[0];
				else
					cmd_path = find_path(argv[0]);

				/* Command not found */
				if (!cmd_path)
				{
					write(STDERR_FILENO, "./hsh: 1: ", 10);
					write(STDERR_FILENO, argv[0], strlen(argv[0]));
					write(STDERR_FILENO, ": not found\n", 13);
					free_argv(argv);
					free(line);
					exit(127);
				}

				/* Execute command */
				pid = fork();
				if (pid == 0)
				{
					execve(cmd_path, argv, environ);
					exit(1);
				}
				wait(NULL);
			}
			free_argv(argv);
		}
	}
	free(line);
	return (0);
}

