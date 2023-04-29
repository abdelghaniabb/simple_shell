#include "main.h"
/**
  * execute_cmd - exeuc
  * @tokens: token
  * @av: value
  * @path: the path
  * Return: 0 - 1
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
	return (WEXITSTATUS(status));
}
