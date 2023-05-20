#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_ARGUMENTS 64
#define MAX_COMMAND_LENGTH 1024

int pass_arguments(char *command, char **arguments);
int executeCommand(char **arguments, char **envp);
int check_command(char *command);
void init_ptrs(char *arg_ptr[], char *buff);

#endif /* _SHELL_H_ */
