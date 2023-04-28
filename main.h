#ifndef MN
#define MN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int _strcmp(char *s1, char *s2);
void error(char *name, int counter, char *command);
int is_whitespace(char *c);
unsigned int _strlen(char *s);
void print_env(void);
#endif
