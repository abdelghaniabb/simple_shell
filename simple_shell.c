#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024

int main(int argc, char *argv[])
{
	char line[MAX_LINE];
	char *arg[MAX_LINE/2 + 1];
	int should_run = 1;
	pid_t pid;
	int status;

	if (argc > 1)
		printf("one arg");
	while (should_run)
	{
		printf("#cisfun$ ");
		fflush(stdout);
		fgets(line, MAX_LINE, stdin);
		if (line[strlen(line)-1] == '\n')
		{
			line[strlen(line)-1] = '\0';
		}
		if (strcmp(line, "exit") == 0)
		{
			should_run = 0;
			break;
		}
		pid = fork();
		if (pid < 0)
		{
			perror(argv[0]);
			exit(1);
		}
		else if (pid == 0)
		{
			arg[0] = line;
			arg[1] = NULL;
			if (execve(arg[0], arg, NULL) == -1)
			{
				perror(argv[0]);
				exit(1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
