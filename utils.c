#include "simple_shell.h"

/**
 * _strlen - get length of string
 * @s: string
 *
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;

	return (i);
}

/**
 * _strdup - duplicate a string
 * @str: string
 *
 * Return: pointer to new string
 */
char *_strdup(char *str)
{
	int i, len;
	char *dup;

	if (!str)
		return (NULL);

	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = str[i];

	dup[i] = '\0';
	return (dup);
}

/**
 * _strncmp - compare strings
 * @s1: string 1
 * @s2: string 2
 * @n: bytes
 *
 * Return: difference
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0')
			return (0);
	}

	return (0);
}

/**
 * build_path - build full path
 * @dir: directory
 * @cmd: command
 *
 * Return: full path
 */
char *build_path(char *dir, char *cmd)
{
	int len;
	char *path;

	len = _strlen(dir) + _strlen(cmd) + 2;
	path = malloc(sizeof(char) * len);
	if (!path)
		return (NULL);

	strcpy(path, dir);
	strcat(path, "/");
	strcat(path, cmd);

	return (path);
}

/**
 * trim_spaces - remove leading and trailing spaces
 * @str: string to trim
 *
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	end = str + _strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';

	return (str);
}

