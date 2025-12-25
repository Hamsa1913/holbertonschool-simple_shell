#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
 * hsh_loop - main shell loop
 */
void hsh_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		if (line[0] == '\n')
			continue;

		line[read - 1] = '\0';

		pid = fork();
		if (pid == 0)
		{
			if (execve(line, NULL, environ) == -1)
			{
				perror("./hsh");
				exit(1);
			}
		}
		else if (pid > 0)
			wait(&status);
	}
}
