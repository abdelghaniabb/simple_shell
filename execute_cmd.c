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
 * @args: array of command arguments
 * @shell_name: name of the shell
 * @path: path to command executable
 *
 * Return: exit status of the command
 */
int execute_cmd(char **args, char *shell_name, char *path)
{
    pid_t pid;
    int status;
    int pipefd[2];
    int fd_in = 0;
    int i = 0;
    int num_cmds = 1;
    char **cmds[256] = {NULL};
    char **cmd;

    /* Split command into multiple commands if it contains pipes*/
    for (i = 0, cmd = args; *cmd; cmd++)
    {
        if (strcmp(*cmd, "|") == 0)
        {
            *cmd = NULL;
            cmds[num_cmds - 1] = args + i;
            i = cmd - args + 1;
            num_cmds++;
        }
    }
    cmds[num_cmds - 1] = args + i;

    /* Execute commands in a pipeline*/
    for (i = 0; i < num_cmds; i++)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process*/
            dup2(fd_in, 0);
            if (i < num_cmds - 1)
            {
                /* Not the last command, redirect stdout to pipe*/
                dup2(pipefd[1], 1);
            }
            close(pipefd[0]);
            close(pipefd[1]);

            execve(path, cmds[i], environ);
            perror(shell_name);
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process*/
            close(pipefd[1]);
            fd_in = pipefd[0];
        }
    }

    /* Wait for all child processes to exit and retrieve their exit status*/
    for (i = 0; i < num_cmds; i++)
    {
        waitpid(-1, &status, 0);
        if (WIFEXITED(status))
        {
            status = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            status = 128 + WTERMSIG(status);
        }
    }

    return status;
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
