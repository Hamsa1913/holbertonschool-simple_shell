#include "simple_shell.h"

/**
 * find_path - find command in PATH
 */
char *find_path(char *cmd)
{
	char *path = NULL, *path_copy, *token, *full;
	int i;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (_strdup(cmd));

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			path = environ[i] + 5;
	}

	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		full = malloc(_strlen(token) + _strlen(cmd) + 2);
		if (!full)
			return (NULL);

		sprintf(full, "%s/%s", token, cmd);

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
