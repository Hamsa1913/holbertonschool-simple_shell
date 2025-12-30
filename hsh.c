#include "simple_shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int execute(char **args)
{
    pid_t pid;
    int status, i;
    char *path_env = NULL, *dir, full_path[1024];
    int found = 0;

    /* Find PATH from environ */
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
    }

    /* Check if full path provided */
    if (strchr(args[0], '/'))
    {
        if (access(args[0], X_OK) != -1)
            found = 1;
    }
    else if (path_env)
    {
        char *path_dup = strdup(path_env);
        dir = strtok(path_dup, ":");
        while (dir)
        {
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
            if (access(full_path, X_OK) == 0)
            {
                args[0] = full_path;
                found = 1;
                break;
            }
            dir = strtok(NULL, ":");
        }
        free(path_dup);
    }

    if (!found)
    {
        fprintf(stderr, "%s: not found\n", args[0]);
        return 127;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(args[0], args, environ);
        perror(args[0]);
        exit(127);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }

    return 0;
}
