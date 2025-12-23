#include "simple_shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	(void)ac;
	return (hsh_loop(av[0]));
}
