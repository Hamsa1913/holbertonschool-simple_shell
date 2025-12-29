#include "simple_shell.h"
#include <string.h>

/**
 * _getenv - get environment variable
 * @name: variable name
 *
 * Return: value or NULL
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 &&
		    environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

