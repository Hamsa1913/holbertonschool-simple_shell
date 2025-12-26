#include "simple_shell.h"

/**
 * _strlen - get string length
 */
size_t _strlen(const char *s)
{
    size_t i = 0;
    while (s[i])
        i++;
    return i;
}

/**
 * _strdup - duplicate string
 */
char *_strdup(const char *s)
{
    size_t len = _strlen(s) + 1;
    char *dup = malloc(len);
    size_t i;

    if (!dup)
        return NULL;

    for (i = 0; i < len; i++)
        dup[i] = s[i];
    return dup;
}

/**
 * _strncmp - compare n characters
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
    return 0;
}

/**
 * trim_spaces - trim leading and trailing spaces
 */
char *trim_spaces(char *str)
{
    char *end;
    while (*str && (*str == ' ' || *str == '\t'))
        str++;
    end = str + _strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        *end-- = '\0';
    return str;
}

/**
 * _memcpy - copy memory
 */
void _memcpy(void *dest, void *src, size_t n)
{
    size_t i;
    char *d = dest;
    char *s = src;

    for (i = 0; i < n; i++)
        d[i] = s[i];
}
