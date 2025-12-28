#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char **environ;

/**
 * hsh_loop - Main shell loop, reads and executes commands
 *
 * Return: 0 on success
 */
int hsh_loop(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **argv;
    pid_t pid;

    
    while (1)
    {
        /* Print prompt */
        write(STDOUT_FILENO, "$ ", 2);

        /* Read input line */
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        /* Remove newline */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Skip empty lines */
        if (line[0] == '\0')
            continue;

        /* Split line into arguments */
        argv = split_line(line);
        if (!argv)
            continue;

        /* Check for exit command */
        if (strcmp(argv[0], "exit") == 0)
        {
            free_argv(argv);
            break;
        }

        /* Fork to execute command */
        pid = fork();
        if (pid == 0)
        {
            /* Child process */
            if (access(argv[0], F_OK) != 0)
            {
                char *full_path = find_path(argv[0]);
                if (!full_path)
                {
                    write(STDERR_FILENO, "execve: No such file or directory\n", 34);
                    free_argv(argv);
                    exit(EXIT_FAILURE);
                }
                execve(full_path, argv, environ);
                free(full_path);
            }
            else
            {
                execve(argv[0], argv, environ);
            }

            perror("execve");
            free_argv(argv);
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            /* Parent waits for child */
            wait(NULL);
        }
        else
        {
            perror("fork");
        }

        free_argv(argv);
    }

    free(line);
    return 0;
}
