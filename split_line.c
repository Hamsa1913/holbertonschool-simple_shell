#include "simple_shell.h"
#include <string.h>  /* مهم عشان strtok */

#include <stdlib.h>

/**
 * split_line - Splits a line into arguments
 * @line: Input line
 * Return: Array of tokens
 */
char **split_line(char *line)
{
    char **tokens;
    char *token;
    int i = 0;

    tokens = malloc(sizeof(char *) * 1024);
    if (!tokens)
        return (NULL);

    token = strtok(line, " \t\n");

    while (token)
    {
        tokens[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;

    return (tokens);
}
