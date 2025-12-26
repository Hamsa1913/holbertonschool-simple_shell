#include "simple_shell.h"

/**
 * find_path - Finds full path of a command using PATH
 */
char *find_path(char *cmd)
{
    int i = 0;
    char *path, *path_copy, *token, *full;
    size_t len;

    if (access(cmd, X_OK) == 0)
        return (_strdup(cmd));

    while (environ[i])
    {
        if (_strncmp(environ[i], "PATH=", 5) == 0)
            break;
        i++;
    }
    if (!environ[i])
        return (NULL);

    path = environ[i] + 5;
    path_copy = _strdup(path);
    if (!path_copy)
        return (NULL);

    token = strtok(path_copy, ":");
    while (token)
    {
        len = _strlen(token) + 1 + _strlen(cmd) + 1;
        full = malloc(len);
        if (!full)
        {
            free(path_copy);
            return (NULL);
        }
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
