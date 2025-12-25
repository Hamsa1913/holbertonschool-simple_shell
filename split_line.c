#include "simple_shell.h"

/**
 * split_line - splits a line into arguments
 * @line: the command line
 * Return: NULL-terminated argv array
 */
char **split_line(char *line)
{
	char **argv;
	int bufsize = 64, i = 0;
	char *token;

	argv = malloc(sizeof(char *) * bufsize);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	while (token)
	{
		argv[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			argv = realloc(argv, sizeof(char *) * bufsize);
			if (!argv)
				return (NULL);
		}
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	return (argv);
}

