#include "main.h"

/**
  * env_name_cmp - compare env name with name
  * @env: env
  * @name: env name
  * Return: 0 or length
  */
int env_name_cmp(char *env, char *name)
{
	int i = 0;

	while (env[i] != '=')
	{
		if (env[i] != name[i])
			return (0);
		i++;
	}
	return (i + 1);
}
/**
 * print_env - print env
 * Return: void
 */
void print_env(void)
{
	size_t i = 0, len = 0;

	while (environ[i])
	{
		len = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
/**
 * _getenv - print env
 * @name: env name
 * Return: char
 */
char *_getenv(char *name)
{
	char *result = NULL;
	int i = 0, mov_to = 0;

	while (environ[i] != NULL)
	{
		mov_to = env_name_cmp(environ[i], name);

		if (mov_to != 0)
		{
			result = environ[i];
			break;
		}
		i++;
	}
	return (result + mov_to);
}
/**
 * search_command - search command
 * @command: the command
 * @fullpath: the path
 * @path: the path
 * Return: char
 */
char *search_command(char *command, char *fullpath, char *path)
{
	unsigned int command_len, path_len;
	char *path_copy, *token;

	command_len = _strlen(command);

	path_copy = malloc(sizeof(char) * _strlen(path) + 1);
	_strcpy(path_copy, path);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		path_len = _strlen(token);
		fullpath = malloc(sizeof(char) * (path_len + command_len) + 2);
		if (fullpath == NULL)
			return (NULL);

		_strcpy(fullpath, token);
		fullpath[path_len] = '/';
		_strcpy(fullpath + path_len + 1, command);
		fullpath[path_len + command_len + 1] = '\0';
		if (access(fullpath, X_OK) != 0)
		{
			free(fullpath);
			fullpath = NULL;
			token = strtok(NULL, ":");
		}
		else
			break;
	}
	free(path_copy);
	return (fullpath);
}

