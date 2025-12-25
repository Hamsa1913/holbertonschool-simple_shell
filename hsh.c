#include "simple_shell.h"

/**
 * hsh_loop - Main shell loop
 * Return: 0 on success
 */
int hsh_loop(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t r;
    pid_t pid;
    int status;
    char **argv;
    char *cmd_path;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        r = getline(&line, &len, stdin);
        if (r == -1)
        {
            free(line);
            return (0);
        }

        if (r > 0 && line[r - 1] == '\n')
            line[r - 1] = '\0';

        line = trim_spaces(line);
        if (*line == '\0')
            continue;

        argv = split_line(line);
        if (!argv || !argv[0])
        {
            free(argv);
            continue;
        }

        cmd_path = find_path(argv[0]);

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(argv);
            free(line);
            return (0);
        }

        if (pid == 0)
        {
            if (execve(cmd_path ? cmd_path : argv[0], argv, environ) == -1)
            {
                perror("./hsh");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(&status);

        free(argv);
        if (cmd_path)
            free(cmd_path);
    }

    free(line);
    return (0);
}
