#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * hsh_loop - main shell loop
 * Return: 0 on success
 */
int hsh_loop(void)
{
    char *line = NULL, **argv;
    size_t n = 0;
    ssize_t read;
    int status = 0;

    while (1)
    {
        /* Print prompt */
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        read = getline(&line, &n, stdin);
        if (read == -1) /* EOF or error */
        {
            free(line);
            break;
        }

        /* Remove leading/trailing spaces and newline */
        line[read - 1] = '\0'; /* remove newline */
        line = trim_spaces(line);

        if (line[0] == '\0') /* empty line */
            continue;

        argv = split_line(line);
        if (!argv)
            continue;

        /* Check if command exists before fork */
        if (access(argv[0], F_OK) == 0 || find_in_path(argv[0]))
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                free_argv(argv);
                continue;
            }
            else if (pid == 0) /* Child process */
            {
                execve(argv[0], argv, environ);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            else /* Parent process */
                waitpid(pid, &status, 0);
        }
        else
        {
            write(STDOUT_FILENO, argv[0], _strlen(argv[0]));
            write(STDOUT_FILENO, ": command not found\n", 20);
        }

        free_argv(argv);
    }

    free(line);
    return (0);
}

/**
 * main - entry point for simple shell
 * Return: 0 on success
 */
int main(void)
{
    return (hsh_loop());
}

