#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;

int hsh_loop(void);
char *find_path(char *command);

#endif
