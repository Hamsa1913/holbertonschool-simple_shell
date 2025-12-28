#include "simple_shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

char *find_path(const char *command)
{
	int i = 0;
	char *path_env, *path_copy, *token, *full;
	size_t len;

	if (access(command, X_OK) == 0)
		return _strdup(command);

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
		i++;
	}
	if (!environ[i])
		return NULL;

	path_copy = _strdup(path_env);
	if (!path_copy)
		return NULL;

	token = strtok(path_copy, ":");
	while (token)
	{
		len = strlen(token) + strlen(command) + 2;
		full = malloc(len);
		if (!full)
		{
			free(path_copy);
			return NULL;
		}
		snprintf(full, len, "%s/%s", token, command);
		if (access(full, X_OK) == 0)
		{
			free(path_copy);
			return full;
		}
		free(full);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return NULL;
}

