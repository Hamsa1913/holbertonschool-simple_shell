#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

/**
 * hsh_loop - main shell loop
 * Return: 0
 */
int hsh_loop(void)
{
	char *line = NULL, *cmd_path = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	pid_t pid;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (*line == '\0')
			continue;

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free_argv(argv);
			continue;
		}

		/* Resolve command BEFORE fork */
		if (strchr(argv[0], '/'))
			cmd_path = argv[0];
		else
			cmd_path = find_path(argv[0]);

		if (!cmd_path)
		{
			write(STDERR_FILENO,
			      "execve: No such file or directory\n", 34);
			free_argv(argv);
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			execve(cmd_path, argv, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);

		if (cmd_path != argv[0])
			free(cmd_path);

		free_argv(argv);
	}

	free(line);
	return (0);
}
