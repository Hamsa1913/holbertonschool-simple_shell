#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* main loop function */
int hsh_loop(void);

/* path functions */
char *find_path(char *cmd);
void trim_spaces(char *str);

/* utility file functions becuse i cant used more than 5 functions */
size_t _strlen(const char *s);
char *_strdup(const char *s);
int _strncmp(char *s1,  char *s2, size_t n);
void *_memcpy(void *dest, const void *src, size_t n);

/*split line into argument*/
char **split_line(char *line);
#endif
