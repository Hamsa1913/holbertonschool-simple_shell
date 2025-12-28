#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stddef.h>

/* Main shell loop */
int hsh_loop(void);

/* Utility functions */
size_t _strlen(const char *s);
char *_strdup(const char *s);
void *_memcpy(void *dest, const void *src, size_t n);
char *trim_spaces(char *str);
void free_argv(char **argv);

/* Path handling */
char *find_path(const char *command);

#endif
