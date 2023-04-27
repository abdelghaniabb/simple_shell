#include "main.h"


/**
  * main - entry point to shell
  * @argc: arg number
  * @av: argv
  * Return: -1 | 1
  */

int main(int __attribute__((unused)) argc, char *av[])
{
	char *buffer = NULL;
	char *list[2];
	int status;
	size_t buf_s = 0, ssize_t len = 0;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		len = getline(&buffer, &buf_s, stdin);
		if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[len - 1] = '\0';
			pid = fork();
			if (pid < 0)
			{
				perror("Error: "), free(buffer);
				exit(8);
			}
			else if (pid == 0)
			{
				list[0] = buffer, list[1] = NULL;
				if (execve(list[0], list, NULL) < -0)
					perror(av[0]), free(buffer), exit(8);
			}
			else
			{
				wait(&status);
				if (status < 0)
					free(buffer), exit(8);
				free(buffer);
			}
			fflush(stdin), buffer = NULL, buf_s = 0;
		}
	}
	if (len == -1)
		return (EXIT_FAILURE);
	return (0);
}
