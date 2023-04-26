#ifndef MN
#define MN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
void waitpid(int status, pid_t pid):


extern char **environ;
#define PROMPT "#cisfun$ "

size_t replace_char(char *str, char old_char, char new_char);
void execute_command(char *command, char *argv);

#endif
