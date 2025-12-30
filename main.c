#include "simple_shell.h"
#include <string.h>

int main(void)
{
    char *line = NULL;
    char **args;
    size_t len = 0;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);

        if (getline(&line, &len, stdin) == -1)
            break;

        args = split_line(line);

        if (args[0] == NULL)
        {
            free(args);
            continue;
        }

        /* built-in exit */
        if (strcmp(args[0], "exit") == 0)
        {
            free(args);
            free(line);
            exit(0);
        }

        execute(args);
        free(args);
    }

    free(line);
    return (0);
}
