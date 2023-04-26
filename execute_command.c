#include "main.h"
/**
 * execute_command - check
 * @command: var1
 * @argv: var2
 * Return: void
 */
void execute_command(char *command, char *argv)
{
	pid_t pid;
/*	pid_t wpid;*/
/*	int status;*/
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
			perror(argv);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror(argv);
		/*exit(1);*/
	}
	else
	{
		/*waitpid(pid, &status, 0);*/
		wait(NULL);
	}
	free(args);
}
