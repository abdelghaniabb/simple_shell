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
		if (isatty(STDIN_FILENO) == 1 && isatty(STDOUT_FILENO) == 1)
			write(1, "$ ", 2);
		length = getline(&buffer, &size, stdin);
		if (buffer[length - 1] == '\n')
			buffer[length - 1] = '\0';
		if (_strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(0);
		}
		if (length < 0)
			break;
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			return (1);
		}
		if (pid == 0)
		{
			list[0] = buffer, list[1] = NULL;
			execve(list[0], list, NULL);
			perror(av[0]);
			free(buffer);
			exit(98);
		}
		else
		{
			wait(&status);
		}
	}
	if (length < 0 && isatty(STDIN_FILENO) == 1 && isatty(STDOUT_FILENO) == 1)
		write(STDERR_FILENO, "\n", 1);
	free(buffer);
	return (0);
}
