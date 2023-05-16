#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void promptuser(char **argv, char **envp);
void exec_command(char *arg_ptr[], char **argv, char **envp);
void init_ptrs(char *arg_ptr[], char *buff);

#endif /* _SHELL_H_ */
