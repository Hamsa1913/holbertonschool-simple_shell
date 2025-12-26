#include "simple_shell.h"

/**
 * hsh_loop - Main shell loop
 */
void hsh_loop(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    char **argv;
    char *cmd_path;
    pid_t pid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, ":) ", 3);
        nread = getline(&line, &bufsize, stdin);
        if (nread == -1)
        {
            free(line);
            exit(EXIT_SUCCESS);
        }

        _trim_spaces(line);
        if (_strlen(line) == 0)
            continue;

        argv = split_line(line);
        if (!argv[0])
        {
            free(argv);
            continue;
        }

        cmd_path = find_path(argv[0]);
        if (!cmd_path)
        {
            write(STDERR_FILENO, argv[0], _strlen(argv[0]));
            write(STDERR_FILENO, ": not found\n", 12);
            for (int i = 0; argv[i]; i++)
                free(argv[i]);
            free(argv);
            continue;
        }

        pid = fork();
        if (pid == 0)
        {
            execve(cmd_path, argv, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
            waitpid(pid, &status, 0);
        else
            perror("fork");

        free(cmd_path);
        for (int i = 0; argv[i]; i++)
            free(argv[i]);
        free(argv);
    }
}

/**
 * main - Entry point
 */
int main(void)
{
    hsh_loop();
    return (0);
}

