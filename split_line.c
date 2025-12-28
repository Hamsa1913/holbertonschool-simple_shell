#include "simple_shell.h"
#include <stdlib.h>
#include <string.h>

char **split_line(char *line)
{
	int bufsize = 64, pos = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		return NULL;

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[pos++] = _strdup(token);
		if (pos >= bufsize)
		{
			bufsize *= 2;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				return NULL;
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[pos] = NULL;
	return tokens;
}
