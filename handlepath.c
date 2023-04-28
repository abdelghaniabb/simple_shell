#include "main.h"


void print_env(void)
{
	unsigned int i = 0;

	while(environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
