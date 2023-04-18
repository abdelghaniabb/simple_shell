#include "main.h"

void execute_command(char *command)
{
	pid_t pid, wpid;
	int status;
	char *args[] = {command, NULL};;
	char **environ;
	
	pid = fork();
	
	if (pid == 0)
	{
		//*args[] = {command, NULL};
		if (execve(*args, args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		//exit(1);
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, 0);
		}while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
