#include "simple_shell.h"

/**
 * _strlen - returns length of a string
 */
size_t _strlen(const char *s)
{
	size_t i = 0;

	if (!s)
		return (0);

	while (s[i])
		i++;

	return (i);
}

/**
 * _strdup - duplicates a string
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

	for (i = 0; i < len; i++)
		dup[i] = s[i];

	dup[i] = '\0';
	return (dup);
}

/**
 * _memcpy - copies
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
 * trim_spaces - removes leading/trailing spaces
 */
void trim_spaces(char *str)
{
	int start = 0, end, i;

	if (!str)
		return;

	while (str[start] == ' ' || str[start] == '\t')
		start++;

	end = _strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'))
		end--;

	for (i = 0; start <= end; start++, i++)
		str[i] = str[start];

	str[i] = '\0';
}

/**
 * split_line - splits line into arguments
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

