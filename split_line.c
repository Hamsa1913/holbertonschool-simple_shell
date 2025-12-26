#include "simple_shell.h"

/**
 * split_line - split line into arguments
 */
char **split_line(char *line)
{
    int bufsize = 64, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
        return NULL;

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[pos++] = token;
        if (pos >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
                return NULL;
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[pos] = NULL;
    return tokens;
}
