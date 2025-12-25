#include "simple_shell.h"

/**
 * hsh_loop - shell loop
 */
int hsh_loop(void)
{
	char *line = NULL, *cmd, *path;
	size_t len = 0;
	ssize_t r;
	pid_t pid;
	int status;
	char **argv;

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

		cmd = trim_spaces(line);

		if (*cmd == '\0')
			continue;

		_memcpy(line, cmd, _strlen(cmd) + 1);

		argv = split_line(line);
		if (!argv)
			continue;

		path = find_path(argv[0]);
		if (!path)
		{
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			free(argv);
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			execve(path, argv, environ);
			exit(1);
		}
		else
		{
			wait(&status);
			free(path);
			free(argv);
		}
	}
}

