#include "simple_shell.h"

/**
 * hsh_loop - main shell loop
 *
 * Return: 0
 */
int hsh_loop(void)
{
	char *line;
	size_t len;
	ssize_t r;
	pid_t pid;
	int status;
	char *argv[2];
	char *cmd_path;

	line = NULL;
	len = 0;

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

		if (line[r - 1] == '\n')
			line[r - 1] = '\0';

		if (*line == '\0')
			continue;

		cmd_path = find_path(line);
		if (cmd_path == NULL)
		{
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, line, _strlen(line));
			write(STDERR_FILENO, ": not found\n", 12);
			continue;
		}

		argv[0] = cmd_path;   /* fixing this line and adding null */
		argv[1] = NULL;

		pid = fork();
		if (pid == 0)
		{
			execve(cmd_path, argv, environ);
			exit(1);
		}
		else
			wait(&status);

		free(cmd_path);
	}
}

