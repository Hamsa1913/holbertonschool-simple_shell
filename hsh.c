#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int hsh_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t r;
	int interactive;
	pid_t pid;
	int status;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		r = getline(&line, &len, stdin);
		if (r == -1)
		{
			free(line);
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			return (0);
		}

		if (r > 0 && line[r - 1] == '\n')
			line[r - 1] = '\0';

		if (line[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			char *argv[] = {line, NULL};

			if (execve(argv[0], argv, environ) == -1)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
				free(line);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
}
