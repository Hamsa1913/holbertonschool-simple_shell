#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/* shell */
int hsh_loop(void);

/* utils */
char *trim_spaces(char *str);
char **split_line(char *line);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *s);
void _memcpy(char *dest, char *src, int n);

/* path */
char *find_path(char *cmd);

#endif

