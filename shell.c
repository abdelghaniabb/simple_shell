#include "main.h"

/**
  * main - entry point to shell
  * @argc: arg number
  * @av: arg value
  * Return: -1 | 1
  */

#include "main.h"

/**
  * main - entry point to shell
  * @argc: arg number
  * @av: arg value
  * Return: -1 | 1
  */

/**
 * set_env - set or update the value of an environment variable
 * @tokens: an array of command arguments
 *
 * Return: 0 on success, -1 on failure
 */
int set_env(char **tokens)
{
    if (tokens[1] == NULL || tokens[2] == NULL)
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return -1;
    }

    if (setenv(tokens[1], tokens[2], 1) == -1)
    {
        perror("setenv");
        return -1;
    }

    return 0;
}

/**
 * unset_env - remove an environment variable
 * @tokens: an array of command arguments
 *
 * Return: 0 on success, -1 on failure
 */
int unset_env(char **tokens)
{
    if (tokens[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return -1;
    }

    if (unsetenv(tokens[1]) == -1)
    {
        perror("unsetenv");
        return -1;
    }

    return 0;
}

int main(int __attribute__((unused)) argc, char *av[])
{
    char *buffer = NULL, *path_env, *path, **tokens, st = 0;
    size_t buf_s = 0;
    int flag = 0, len = 0;

    while (1)
    {
        if (strcmp(tokens[0], "setenv") == 0)
        {
            set_env(tokens);
            continue;
        }
        else if (strcmp(tokens[0], "unsetenv") == 0)
        {
            unset_env(tokens);
            continue;
        }

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
            free(buffer), free(tokens), exit(st);
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

/*
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
			free(buffer), free(tokens), exit(st);
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
*/
