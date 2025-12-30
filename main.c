#include "simple_shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *line = NULL;
    char **args;
    size_t len = 0;
    int status = 0;
    int i;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        if (getline(&line, &len, stdin) == -1)
            break;

        args = split_line(line);

        if (args[0] == NULL)
        {
            free(args);
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            free(args);
            free(line);
            exit(status);
        }

        if (strcmp(args[0], "env") == 0)
        {
            for (i = 0; environ[i]; i++)
                printf("%s\n", environ[i]);
            free(args);
            continue;
        }

        status = execute(args);
        free(args);
    }

    free(line);
    return (0);
}
