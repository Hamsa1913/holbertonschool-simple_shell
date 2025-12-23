#include "simple_shell.h"

/**
 * shell_loop - Runs the main shell loop
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		if (getline(&line, &len, stdin) == -1)
			break;
	}

	free(line);
}
