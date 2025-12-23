#include "simple_shell.h"

/**
 * main - Entry point for simple shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

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
			if (execve(line, argv, environ) == -1)
			{
				perror(argv[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
