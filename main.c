#include "simple_shell.h"

/**
 * main - Entry point for simple shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	hsh_loop();
	return (0);
}
