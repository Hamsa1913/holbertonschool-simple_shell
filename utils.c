#include "simple_shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
 * _strlen - Returns the length of a string
 */
size_t _strlen(const char *s)
{
    size_t len = 0;

    while (s[len])
        len++;
    return (len);
}

/**
 * _strdup - Duplicates a string (allocates)
 */
char *_strdup(const char *s)
{
    char *dup;
    size_t i, len;

    if (!s)
        return (NULL);

    len = _strlen(s);
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);

    for (i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';

    return (dup);
}

/**
 * _memcpy - Copies memory area
 */
void _memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    char *d = (char *)dest;
    char *s = (char *)src;

    for (i = 0; i < n; i++)
        d[i] = s[i];
}

/**
 * trim_spaces - Remove leading and trailing spaces/tabs
 */
char *trim_spaces(char *str)
{
    char *end;

    if (!str)
        return (NULL);

    /* Trim leading spaces */
    while (*str && (*str == ' ' || *str == '\t'))
        str++;

    if (*str == 0) /* all spaces */
        return str;

    /* Trim trailing spaces */
    end = str + _strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';

    return str;
}

/**
 * free_argv - Frees a NULL-terminated array of strings
 */
void free_argv(char **argv)
{
    int i;

    if (!argv)
        return;

    for (i = 0; argv[i]; i++)
        free(argv[i]);
    free(argv);
}

