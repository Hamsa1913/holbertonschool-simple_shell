#include "simple_shell.h"

/**
 * _strlen - returns length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
    int i = 0;

    while (s[i])
        i++;
    return (i);
}
