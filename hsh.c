#include "simple_shell.h"

/**
 * hsh_loop - Main shell loop
 *
 * Return: 0 on success
 */
int hsh_loop(void)
{
	char *line;
	char **argv;
	char *cmd_path;
	size_t len;
	ssize_t read;
	pid_t pid;
	int status;

	line = NULL;
	len = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			return (0);
		}

		/* Remove trailing newline */
		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Trim leading/trailing spaces */
		trim_spaces(line);

		/* Empty or spaces-only line */
		if (line[0] == '\0')
			continue;

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free(argv);
			continue;
		}

		/* Find command path */
		cmd_path = find_path(argv[0]);
		if (!cmd_path)
		{
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);

			free(argv);
			continue;
		}

		/* Fork only if command exists */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(cmd_path);
			free(argv);
			continue;
		}

		if (pid == 0)
		{
			execve(cmd_path, argv, environ);
			perror("execve");
			exit(1);
		}
		else
		{
			wait(&status);
		}

		free(cmd_path);
		free(argv);
	}
}
