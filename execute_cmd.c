#include "main.h"
/**
  * execute_cmd - exeuc
  * @tokens: token
  * @av: value
  * @path: the path
  * Return: 0 - 1
  */

/**
 * execute_cmd - execute a command
 * @tokens: the command and its arguments
 * @av: the name of the shell
 * @path: the path to the command
 * Return: the exit status of the command
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
    {
        if (wait(&status) == -1)
        {
            perror("wait");
            exit(2);
        }

        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            fprintf(stderr, "%s: %s terminated by signal %d\n", av, tokens[0], WTERMSIG(status));
            return 128 + WTERMSIG(status);
        }
        else
        {
            fprintf(stderr, "%s: %s exited abnormally\n", av, tokens[0]);
            return 2;
        }
    }
    return 0;
}

/*
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
*/
