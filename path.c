#include "simple_shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * get_path_from_environ - finds PATH variable in environ
 *
 * Return: pointer to PATH string, or NULL if not found
 */
char *get_path_from_environ(void)
{
	int i;
	char *prefix = "PATH=";
	size_t len = strlen(prefix);

	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], prefix, len) == 0)
			return (environ[i] + len);
		i++;
	}
	return (NULL);
}

/**
 * find_path - finds full path of command in PATH
 * @command: command name
 *
 * Return: malloc'd full path if found, else NULL
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *token;
	char *full_path;
	size_t len;

	path_env = get_path_from_environ();
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		len = strlen(token) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
			break;

		sprintf(full_path, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

