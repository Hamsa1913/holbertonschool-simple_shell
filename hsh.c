#include "simple_shell.h"

/**
 * trim_spaces - trims leading and trailing spaces/tabs/newlines
 * @s: string to trim
 *
 * Return: pointer to first non-space char inside s
 */
static char *trim_spaces(char *s)
{
	size_t len;

	if (s == NULL)
		return (NULL);

	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;

	len = strlen(s);
	while (len > 0 &&
	       (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n'))
	{
		s[len - 1] = '\0';
		len--;
	}
	return (s);
}

/**
 * print_error - prints error like sh
 * @av0: program name
 * @count: command count
 * @cmd: command
 */
static void print_error(char *av0, unsigned int count, char *cmd)
{
	char num[32];
	int i = 30;
	unsigned int n = count;

	num[31] = '\0';
	num[30] = '0';

	while (n > 0 && i >= 0)
	{
		num[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}

	write(STDERR_FILENO, av0, strlen(av0));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, &num[i + 1], strlen(&num[i + 1]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * run_cmd - forks and executes a command (no args)
 * @av0: program name
 * @cmd: command path
 * @count: command count
 */
static void run_cmd(char *av0, char *cmd, unsigned int count)
{
	pid_t pid;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, environ);
		print_error(av0, count, cmd);
		_exit(127);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
}

/**
 * hsh_loop - main loop for shell
 * @av0: argv[0]
 *
 * Return: 0
 */
int hsh_loop(char *av0)
{
	char *line = NULL, *cmd;
	size_t len = 0;
	ssize_t r;
	unsigned int count = 0;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		r = getline(&line, &len, stdin);
		if (r == -1)
			break;

		count++;
		cmd = trim_spaces(line);
		if (cmd == NULL || *cmd == '\0')
			continue;

		if (strcmp(cmd, "exit") == 0)
			break;

		run_cmd(av0, cmd, count);
	}

	free(line);
	return (0);
}
