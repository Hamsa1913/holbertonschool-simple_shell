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
size_t _strlen(const char *s);
char *_strdup(const char *s);
int _strncmp(const char *s1, const char *s2, size_t n);
char *trim_spaces(char *str);
void *_memcpy(void *dest, const void *src, size_t n); 

/*split line into argument*/
char **split_line(char *line);
#endif
