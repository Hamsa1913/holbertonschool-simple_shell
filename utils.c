#include "simple_shell.h"

/**
 * _strlen - Returns the length of a string
 */
size_t _strlen(const char *s)
{
	size_t i = 0;

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
char *_strdup(const char *s)
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
int _strncmp( char *s1, char *s2, size_t n)
{
    size_t i;

    	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
	}
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
{
	int start = 0, end, i = 0;

	if (!str)
		return;

	while (str[start] == ' ' || str[start] == '\t')
		start++;

	end = _strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'))
		end--;

	while (start <= end)
		str[i++] = str[start++];

	str[i] = '\0';
}

/**
 * split_line - Splits a line into tokens (arguments)
 */
char **split_line(char *line)
{
	char **argv;
	char *token;
	int i = 0;

	if (!line)
		return (NULL);

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	while (token)
	{
		argv[i++] = _strdup(token);
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}
