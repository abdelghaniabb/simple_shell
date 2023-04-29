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
 * _setenv - Set the value of an environment variable
 * @name: The name of the environment variable
 * @value: The value to set
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value)
{
    char *env = malloc(strlen(name) + strlen(value) + 2);
    if (name == NULL || value == NULL)
        return (-1);

    if (env == NULL)
        return (-1);

    sprintf(env, "%s=%s", name, value);
    if (putenv(env) != 0) {
        free(env);
        return (-1);
    }

    return (0);
}

int main(int __attribute__((unused)) argc, char *av[])
{
    char *buffer = NULL, *path_env, *path, **tokens, st = 0;
    size_t buf_s = 0;
    int flag = 0, len = 0;
    char *pwd;

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
        if (_strcmp(tokens[0], "cd") == 0)
        {
            if (tokens[1] == NULL)
                path = _getenv("HOME");
            else if (_strcmp(tokens[1], "-") == 0)
            {
                path = _getenv("OLDPWD");
                printf("%s\n", path);
            }
            else
                path = tokens[1];
            pwd = getcwd(NULL, 0);
            if (chdir(path) == -1)
            {
                fprintf(stderr, "cd: can't cd to %s\n", path);
                free(buffer), free(tokens);
                continue;
            }
            _setenv("OLDPWD", pwd);
            free(pwd);
            pwd = getcwd(NULL, 0);
            _setenv("PWD", pwd);
            free(pwd);
            free(buffer), free(tokens);
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
