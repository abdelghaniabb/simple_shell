#ifndef MN
#define MN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
extern char **environ;

size_t replace_char(char *str, char old_char, char new_char);
void execute_command(char *command);

#endif
