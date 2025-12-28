#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stddef.h>

/* Global variable for environment */
extern char **environ;

/* Main loop */
int hsh_loop(void);

/* String and memory utilities */
size_t _strlen(const char *s);
char *_strdup(const char *s);
void *_memcpy(void *dest, const void *src, size_t n);
char *trim_spaces(char *str);

/* Parsing and freeing */
char **split_line(char *line);
void free_argv(char **argv);

/* PATH resolution */
char *find_path(const char *command);

#endif /* SIMPLE_SHELL_H */

