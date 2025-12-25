#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stddef.h>
#include <unistd.h>

extern char **environ;

/* main loop */
void hsh_loop(void);

#endif /* SIMPLE_SHELL_H */
