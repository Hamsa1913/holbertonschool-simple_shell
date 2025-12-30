#include "simple_shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int execute(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            perror(args[0]);
            exit(127); /* command not found */
        }
        exit(0);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }

    return 0;
}
