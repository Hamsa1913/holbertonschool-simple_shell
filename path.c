#include "simple_shell.h"

/**
 * build_path - Build full path string
 * @dir: directory
 * @cmd: command
 * Return: full path
 */
char *build_path(char *dir, char *cmd)
{
    size_t len = _strlen(dir) + _strlen(cmd) + 2;
    char *full = malloc(len);

    if (!full)
        return (NULL);

    _memcpy(full, dir, _strlen(dir));
    full[_strlen(dir)] = '/';
    _memcpy(full + _strlen(dir) + 1, cmd, _strlen(cmd) + 1);

    return full;
}

/**
 * find_path - Search PATH for command
 * @cmd: command
 * Return: full path if found, else NULL
 */
char *find_path(char *cmd)
{
    int i = 0;
    char *path, *path_copy, *token, *full;

    if (cmd[0] == '/' || cmd[0] == '.')
        return (_strdup(cmd));

    while (environ[i])
    {
        if (_strncmp(environ[i], "PATH=", 5) == 0)
            break;
        i++;
    }

    if (!environ[i])
        return NULL;

    path = environ[i] + 5;
    path_copy = _strdup(path);
    if (!path_copy)
        return NULL;

    token = strtok(path_copy, ":");
    while (token)
    {
        full = build_path(token, cmd);
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

