#include "simple_shell.h"

/**
 * _strlen - Returns the length of a string
 */
int _strlen(const char *s)
{
    int len = 0;

    while (s[len])
        len++;
    return (len);
}

/**
 * _strdup - Duplicates a string
 */
char *_strdup(const char *s)
{
    char *dup;
    int len, i;

    if (!s)
        return (NULL);

    len = _strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);

    for (i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';

    return (dup);
}

/**
 * _strncmp - Compare n characters of two strings
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    for (i = 0; i < n && s1[i] && s2[i]; i++)
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    }
    if (i < n)
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return (0);
}

/**
 * _memcpy - Copies n bytes from src to dest
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    char *d = dest;
    const char *s = src;

    for (i = 0; i < n; i++)
        d[i] = s[i];
    return (dest);
}

/**
 * _trim_spaces - Trim leading and trailing spaces from a string
 */
void _trim_spaces(char *str)
{
    char *end;
    int len;

    while (*str == ' ' || *str == '\t')
        str++;

    len = _strlen(str);
    if (len == 0)
    {
        str[0] = '\0';
        return;
    }

    end = str + len - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
}

/**
 * split_line - Splits a line into tokens (arguments)
 */
char **split_line(char *line)
{
    int bufsize = 64, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token != NULL)
    {
        tokens[pos++] = _strdup(token);
        if (pos >= bufsize)
        {
            bufsize *= 2;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n");
    }
    tokens[pos] = NULL;
    return (tokens);
}
