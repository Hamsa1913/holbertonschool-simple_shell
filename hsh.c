#include "simple_shell.h"

/**
 * execute - Executes a command using fork and execve
 * @args: Command arguments
 */
void execute(char **args)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
            perror("Error");
        exit(EXIT_FAILURE);
    }
    else
        wait(NULL);
}
