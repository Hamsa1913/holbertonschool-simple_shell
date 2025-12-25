#include "simple_shell.h"
#include <string.h>

/**
 * find_path - finds command in PATH
 * @command: command name
 *
 * Return: full path or NULL
 */
char *find_path(char *command)
{
        char *path, *path_copy, *token;
        char *full_path;
        size_t len;

        path = getenv("PATH");
        if (!path)
                return (NULL);

        path_copy = strdup(path);
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

