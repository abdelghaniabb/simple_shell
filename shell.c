#include "main.h"


char **make_tokens(char *string)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = (char **)malloc(sizeof(char) * 1024);
	if (tokens == NULL)
	{
		exit(1);
	}
	token = strtok(string, "\n\t\r ");
	if (token == NULL)
		return (NULL);
	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, "\n\t\r ");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * _EOF - buffer is EOF
 * @buffer: string.
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
	exit(0);
}

/**
  * execute_cmd - exeuc
  * @buffer: bfr
  * @av: value
  * Return 0 - 1
  */
int execute_cmd(char **tokens, char *av, char *path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror(av);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
		{
			perror(av);
			exit(2);
		}
	}
	else
		wait(&status);
	return WEXITSTATUS(status);
}

/**
  * main - entry point to shell
  * @argc: arg number
  * @av: arg value
  * Return: -1 | 1
  */

int main(int __attribute__((unused)) argc, char *av[])
{
	char *buffer = NULL, *path_env, *path;
	size_t buf_s = 0;
	ssize_t len = 0;
	int flag = 0;
	char **tokens;
	char st = 0;

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
		buffer[len - 1] = '\0';
		if (is_whitespace(buffer) == 1)
			continue;
		tokens = make_tokens(buffer);
		if (_strcmp(tokens[0], "exit") == 0)
		{
			free(buffer);
			free(tokens);
			exit(st);
		}
		if (_strcmp(tokens[0], "env") == 0)
		{
			free(tokens);
			print_env();
			continue;
		}
		path_env = _getenv("PATH");
		path = search_command(tokens[0], path, path_env);
		if (path == NULL)
			path = tokens[0];
		else
			flag = 1;
		st = execute_cmd(tokens, av[0], path);
		free(buffer);
		buffer = NULL, buf_s = 0;
		free(tokens);
		if (flag == 1)
			free(path);
	}
	return (0);
}
