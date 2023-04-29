#include "main.h"

void p_error(char *av, char *number)
{
	write(STDERR_FILENO, av, _strlen(av));
	write(STDERR_FILENO, ": 1: exit: Illegal number: ", _strlen(": 1: exit: Illegal number: "));
	write(STDERR_FILENO, number, _strlen(number));
	write(STDERR_FILENO, "\n", 1);
}


/**
  * main - entry point to shell
  * @argc: arg number
  * @av: arg value
  * Return: -1 | 1
  */

int main(int __attribute__((unused)) argc, char *av[])
{
	char *buffer = NULL, *path_env, *path, **tokens, st = 0;
	size_t buf_s = 0;
	int flag = 0, len = 0;

	while (1)
	{
		if (isatty(0))
			write(STDOUT_FILENO, "#meisfun$ ", 9);
		len = getline(&buffer, &buf_s, stdin);
		if (len == -1)
			free(buffer), exit(0);
		if (len == EOF)
			_EOF(buffer);
		if (*buffer == '\n')
		{
			free(buffer);
			continue;
		}
		buffer[len - 1] = '\0';
		if (is_whitespace(buffer) == 1)
			continue;
		tokens = make_tokens(buffer);
		if (_strcmp(tokens[0], "exit") == 0)
		{
		   free(buffer), free(tokens), exit(st);
		}
		if (_strcmp(tokens[0], "env") == 0)
		{
			free(tokens), print_env();
			continue;
		}
		path_env = _getenv("PATH"), path = search_command(tokens[0], path, path_env);
		if (path == NULL)
			path = tokens[0];
		else
			flag = 1;
		st = execute_cmd(tokens, av[0], path), free(buffer);
		buffer = NULL, buf_s = 0, free(tokens);
		if (flag == 1)
			free(path);
	}
	return (0);
}

