#include "simple_shell.h"

/**
 * hsh_loop - main shell loop
 */
void hsh_loop(void)
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
			break;

		trim_spaces(line);

		if (line[0] == '\0')
			continue;

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free_argv(argv);
			continue;
		}

		cmd_path = find_path(argv[0]);
		if (!cmd_path)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			free_argv(argv);
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, argv, environ) == -1)
				exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			wait(&status);
		}

		free(cmd_path);
		free_argv(argv);
	}

	free(line);
}

