#include "simple_shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * execute - Executes a command using fork and execve
 * @args: Command arguments
 * Return: status of child process
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            perror(args[0]); /* print error on stderr */
            exit(2);         /* exit with status 2 if command fails */
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
