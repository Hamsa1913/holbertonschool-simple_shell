#include "simple_shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/**
 * hsh_loop - main shell loop
 * Return: 0 on exit
 */
int hsh_loop(void)
{
    char *line = NULL;
    char **argv;
    size_t bufsize = 0;
    ssize_t nread;
    int status;
    pid_t pid;

    while (1)
    {
        /* Print prompt */
        write(STDOUT_FILENO, ":) ", 3);

        /* Read input */
        nread = getline(&line, &bufsize, stdin);
        if (nread == -1)
        {
            free(line);
            break;
        }

        /* Trim leading/trailing spaces */
        trim_spaces(line);

        if (line[0] == '\0') /* Ignore empty lines */
            continue;

        /* Split line into arguments */
        argv = split_line(line);
        if (!argv)
            continue;

        /* Check if command exists */
        if (access(argv[0], F_OK) != 0)
        {
            char *full_path = find_path(argv[0]);
            if (full_path)
            {
                free(argv[0]);
                argv[0] = full_path;
            }
            else
            {
                write(STDERR_FILENO, "Command not found\n", 18);
                free_argv(argv);
                continue;
            }
        }

        /* Fork process */
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free_argv(argv);
            continue;
        }

        if (pid == 0) /* Child */
        {
            execve(argv[0], argv, environ);
            perror("execve"); /* Only reached on error */
            free_argv(argv);
            free(line);
            exit(EXIT_FAILURE);
        }
        else /* Parent */
        {
            waitpid(pid, &status, 0);
        }

        free_argv(argv);
    }

    free(line);
    return (0);
}

/**
 * main - entry point
 * Return: 0 on success
 */
int main(void)
{
    return (hsh_loop());
}

