#include "simple_shell.h"

/**
 * hsh_loop - Simple shell loop
 *
 * Return: 0 on success
 */
int hsh_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t r;
	pid_t pid;
	int status;
	char *argv[2];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		r = getline(&line, &len, stdin);
		if (r == -1)
		{
			free(line);
			return (0);
		}

		if (r > 0 && line[r - 1] == '\n')
			line[r - 1] = '\0';

		if (*line == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			return (0);
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./hsh");
				exit(0);
			}
		}
		else
		{
			wait(&status);
		}
	}
}







