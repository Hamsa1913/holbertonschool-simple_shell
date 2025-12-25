#include "simple_shell.h"

/**
 * find_path - locate command in PATH
 * @cmd: command name
 *
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	int i;
	char *path;
	char *path_copy;
	char *token;
	char *full;

	if (cmd[0] == '/')
		return (_strdup(cmd));

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			path = environ[i] + 5;
	}

	path_copy = _strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		full = build_path(token, cmd);
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
