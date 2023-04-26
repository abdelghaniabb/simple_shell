#include "main.h"

/**
  * main - entry point to shell
  * @argc: arg number
  * @av: argv
  * Return: -1 | 1
  */

int main(int __attribute__((unused)) argc, char *av[])
{
	char *buffer;
	char *list[2];
	int length, status;
	size_t size = 1024;
	pid_t pid;

	buffer = (char *) malloc(sizeof(char) * 1024);
	while (1)
	{
		if (isatty(0))
			write(1, "$ ", 2);
		length = getline(&buffer, &size, stdin);
		buffer[length - 1] = '\0';
		if (_strcmp(buffer, "exit") == 0)
			exit(0);
		if (length == -1)
		{
			exit(0);
		}
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			return (1);
		}
		if (pid == 0)
		{
			list[0] = buffer, list[1] = NULL;
			if (execve(list[0], list, NULL) == -1)
			{
				free(buffer);
				perror(av[0]);
			}
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
