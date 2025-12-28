#include "simple_shell.h"
#include <stdlib.h>
#include <string.h>

/* Return length of string */
size_t _strlen(const char *s)
{
	size_t len = 0;
	while (s[len])
		len++;
	return len;
}

/* Duplicate string */
char *_strdup(const char *s)
{
	size_t len;
	char *dup;
	size_t i;

	if (!s)
		return NULL;
	len = _strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return NULL;
	for (i = 0; i < len; i++)
		dup[i] = s[i];
	dup[i] = '\0';
	return dup;
}

/* Copy memory */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;
	size_t i;

	for (i = 0; i < n; i++)
		d[i] = s[i];
	return dest;
}

/* Trim leading and trailing spaces */
char *trim_spaces(char *str)
{
	char *end;

	if (!str)
		return NULL;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return str;

	end = str + _strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';
	return str;
}

/* Free argv array */
void free_argv(char **argv)
{
	size_t i;

	if (!argv)
		return;

	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
}

