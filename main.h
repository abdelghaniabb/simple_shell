#ifndef MN
#define MN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

char *search_command(char *command, char *fullpath, char *path);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_getenv(char *name);
void error(char *name, int counter, char *command);
int is_whitespace(char *c);
unsigned int _strlen(char *s);
void print_env(void);
#endif
