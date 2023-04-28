#include "main.h"


void print_env(void)
{
	size_t i = 0, len = 0;

	while (environ[i])
	{
		len = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
