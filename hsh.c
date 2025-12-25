#include "simple_shell.h"

/**
 * hsh_loop - main shell loop
 *
 * Return: 0
 */
int hsh_loop(void)
{
	size_t len;
	ssize_t r;
	pid_t pid;
	int status;
	char *argv[2];
	char *cmd_path;
	char *line = NULL;
	char *cmd;

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

		if (r > 0 && line[r - 1] == '\n')
			line[r - 1] = '\0';

		/* trim spaces w\ losing original pointer */
		cmd = trim_spaces(line);

		if (*cmd == '\0')
			continue;

		argv[0] = cmd;
		argv[1] = NULL;

		path = find_path(cmd);
		if (!path)
		{
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, cmd, _strlen(cmd));
			write(STDERR_FILENO, ": not found\n", 12);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(path);
			free(line);
			return (0);
		}

		if (pid == 0)
		{
			execve(path, argv, environ);
			perror("./hsh");
			exit(1);
		}
		else
		{
			wait(&status);
			free(path);
		}
	}
}
