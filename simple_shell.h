#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

extern char **environ;

/* main loop function */
int hsh_loop(void);

/* path functions */
char *find_path(char *cmd);
char *build_path(char *dir, char *cmd);

/* utility file functions becuse i cant used more than 5 functions */
int _strlen(char *s);
char *_strdup(char *str);
int _strncmp(char *s1, char *s2, size_t n);
char *trim_spaces(char *str);

#endif
