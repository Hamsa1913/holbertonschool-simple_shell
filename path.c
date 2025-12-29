#include "simple_shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * find_path - finds command in PATH
 * @cmd: command to find
 *
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	struct stat st;

	path_env = _getenv("PATH");
	if (!path_env || *path_env == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

