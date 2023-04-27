#include "main.h"
/**
 * _EOF - A function that chaecks if buffer is EOF
 * @buffer: The pointer to the input string.
 * Return: Nothing
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}

/**
  * execute_cmd - exeuc
  * @buffer: bfr
  * @av: value
  * @c: counter
  */
void execute_cmd(char *buffer, char *av, int c)
{
	char *list[2];
	pid_t pid;
	int status;

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
			error(av, c, buffer), free(buffer), exit(8);
	}
	else
	{
		wait(&status);
		if (status < 0)
			free(buffer), exit(8);
		free(buffer);
	}
}

/**
  * main - entry point to shell
  * @argc: arg number
  * @av: arg value
  * Return: -1 | 1
  */

int main(int __attribute__((unused)) argc, char *av[])
{
	char *buffer = NULL;
	size_t buf_s = 0;
	ssize_t len = 0;
	int counter = 0;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		len = getline(&buffer, &buf_s, stdin);
		if (len == EOF)
			_EOF(buffer);
		if (*buffer == '\n')
			free(buffer);
		buffer[len - 1] = '\0';
		if (_strcmp(buffer, "exit") == 1)
			free(buffer), exit(0);
		else
		{
			counter++;
			execute_cmd(buffer, av[0], counter);
			fflush(stdin), buffer = NULL, buf_s = 0;
		}
	}
	if (len == -1)
		return (EXIT_FAILURE);
	return (0);
}
