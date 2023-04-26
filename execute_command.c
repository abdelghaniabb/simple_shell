#include "main.h"
void execute_command(char *command)
{
	pid_t pid;
/*	pid_t wpid;*/
	int status;
	char **args = malloc(sizeof(char *) * 2);
	/*char **environ;*/

	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == 0)
	{
		/* *args[] = {command, NULL};*/
		if (execve(*args, args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		/*exit(1);*/
	}
	else
	{
/**
 *		do {
 *			wpid = waitpid(pid, &status, 0);
 *		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
 */
waitpid(pid, &status, 0);
	}
}
