#include "main.h"

char **make_tokens(char *string)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = (char **)malloc(sizeof(char) * 1024);
	if (tokens == NULL)
	{
		perror("Error");
		exit(1);
	}
	token = strtok(string, " ");

	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, "\n\t\r ");
	}
	tokens[i] = NULL;

	return (tokens);
}

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
  * Return 0 - 1
  */
int execute_cmd(char *tokens, char *av)
{
	pid_t pid;
	int status;
	char *l[2];

	l[0] = tokens;
	l[1] = NULL;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(l[0], l, NULL) < 0)
		{
			perror(av);
			return (0);
		}
	}
	else
	{
		wait(&status);
	}
	return (1);
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

	while (1)
	{
		if (isatty(0))
			write(STDOUT_FILENO, "#meisfun$ ", 9);
		len = getline(&buffer, &buf_s, stdin);
		if (len == -1)
		{
			free(buffer);
			exit(0);
		}
		if (len == EOF)
			_EOF(buffer);
		if (*buffer == '\n')
		{
			free(buffer);
			continue;
		}
		else
		{
			buffer[len - 1] = '\0';
			if (execute_cmd(buffer, av[0]) == 0)
				exit(1);
			fflush(stdin), buffer = NULL, buf_s = 0;
		}
	}
	return (0);
}
