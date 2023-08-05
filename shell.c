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
	char *buffer = NULL, *path_env, *path, **tokens /*st = 0*/;
	size_t buf_s = 0;
	int flag = 0, len = 0, exit_status = 0;

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
			/* Handle the exit command with an optional status argument*/
			if (tokens[1] != NULL)
			{
				/* Convert the status argument to an integer*/
				exit_status = atoi(tokens[1]);
				if (exit_status == 0 && tokens[1][0] != '0')
				{
					/* If atoi fails to convert the argument, print an error and continue*/
					p_error(av[0], tokens[1]);
					free(buffer);
					buffer = NULL;
					buf_s = 0;
					free(tokens);
					continue;
				}
			}
			/* Free resources and exit with the specified status*/
			free(buffer);
			free(tokens);
			exit(exit_status);
		}
		else if (_strcmp(tokens[0], "cd") == 0)
		{
			/* Handle the cd command */
			cd_builtin(tokens);
			free(buffer);
			buffer = NULL;
			buf_s = 0;
			free(tokens);
		}
		else if (_strcmp(tokens[0], "env") == 0)
		{
			free(tokens);
			print_env();
			continue;
		}
		else
		{
			path_env = _getenv("PATH");
			path = search_command(tokens[0], path, path_env);
			if (path == NULL)
				path = tokens[0];
			else
				flag = 1;
			/*st = */execute_cmd(tokens, av[0], path);
			free(buffer);
			buffer = NULL, buf_s = 0, free(tokens);
			
			if (flag == 1)
				free(path);
		}
	}
	return (0);
}

