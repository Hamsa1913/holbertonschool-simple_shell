#include "simple_shell.h"
#include <string.h>
#include <stdio.h>

/**
 * hsh_loop - Simple shell main loop
 *
 * Return: 0 on success
 */
int hsh_loop(void)
{
        char *line = NULL;
        size_t len = 0;
        ssize_t r;
        pid_t pid;
        int status;
        char *argv[2];
        char *cmd_path;

        while (1)
        {
                if (isatty(STDIN_FILENO))
                        write(STDOUT_FILENO, "($) ", 4);

                r = getline(&line, &len, stdin);
                if (r == -1)
                {
                        free(line);
                        return (0);
                }

                if (r > 0 && line[r - 1] == '\n')
                        line[r - 1] = '\0';

                if (*line == '\0')
                        continue;

                /* PATH handling */
                cmd_path = find_path(line);
                if (!cmd_path)
                {
                        fprintf(stderr, "./hsh: 1: %s: not found\n", line);
                        continue;
                }

                argv[0] = cmd_path;
                argv[1] = NULL;

                pid = fork();
                if (pid == -1)
                {
                        perror("fork");
                        free(line);
                        free(cmd_path);
                        return (1);
                }

                if (pid == 0)
                {
                        execve(argv[0], argv, environ);
                        _exit(127);
                }
                else
                {
                        wait(&status);
                }

                free(cmd_path);
        }

        free(line);
        return (0);
}

