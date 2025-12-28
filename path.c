#include "simple_shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

extern char **environ;

/**
 * find_path - find command in PATH
 * @cmd: command
 * Return: full path or NULL
 */
char *find_path(const char *cmd)
{
	char *path, *path_copy, *token, *full;
	int i;
	size_t len;

	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}

	if (!path)
		return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		len = strlen(token) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
			break;

		snprintf(full, len, "%s/%s", token, cmd);

		if (access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}

		free(full);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

