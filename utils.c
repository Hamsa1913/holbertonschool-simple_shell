#include "simple_shell.h"

/**
 * _strlen - Returns the length of a string
 */
size_t _strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);

	i = 0;
	while (s[i])
		i++;

	return (i);
}

/**
 * _strdup - Duplicates a string
 */
char *_strdup(char *s)
{
	char *dup;
	size_t i, len;

	if (!s)
		return (NULL);

	len = _strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = s[i];

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
void _memcpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];
}

/**
 * _trim_spaces - Trim leading and trailing spaces from a string
 */
char *trim_spaces(char *str)
{
	int start, end, i;

	if (!str)
		return (NULL);

	start = 0;
	while (str[start] == ' ' || str[start] == '\t')
		start++;

	end = _strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'))
		end--;

	i = 0;
	while (start <= end)
	{
		str[i++] = str[start++];
	}
	str[i] = '\0';

	return (str);
}

/**
 * split_line - Splits a line into tokens (arguments)
 */
char **split_line(char *line)
{
	char **argv;
	char *token;
	int i;

	if (!line)
		return (NULL);

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	i = 0;

	while (token)
	{
		argv[i++] = _strdup(token);
		token = strtok(NULL, " \t");
	}

	argv[i] = NULL;
	return (argv);
}
