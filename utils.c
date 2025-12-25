#include "simple_shell.h"

/**
 * trim_spaces - removes leading and trailing spaces
 */
char *trim_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	char *end = str + _strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	end[1] = '\0';
	return (str);
}

char **split_line(char *line)
{
	char **argv;
	int i = 0;
	char *token;

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	token = strtok(line, " ");
	while (token)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	return (argv);
}

int _strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int _strncmp(char *s1, char *s2, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0')
			return (0);
	}
	return (0);
}

char *_strdup(char *s)
{
	char *dup;
	int len = _strlen(s), i;

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = s[i];

	return (dup);
}

void _memcpy(char *dest, char *src, int n)
{
	int i;
	for (i = 0; i < n; i++)
		dest[i] = src[i];
}
