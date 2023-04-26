#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - check code
 * @argc: argc
 * @argv: argv
 * Return: int
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	char *buffer;
	size_t buffer_size = 1024;
	size_t len;
	char *arg[2];
	pid_t pid;
	int status;

	buffer = (char *) malloc(sizeof(char) * 1024);
	while (1)
	{
		printf("#cisfun$ ");
		len = getline(&buffer, &buffer_size, stdin);
		buffer[len - 1] = '\0';
		if (strcmp(buffer, "exit") == 0)
			break;
		pid = fork();
		if (pid < 0)
		{
			perror(argv[0]);
			exit(1);
		}
		else if (pid == 0)
		{
			arg[0] = buffer;
			arg[1] = NULL;
			if (execve(arg[0], arg, NULL) == -1)
			{
				perror(argv[0]);
				exit(1);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	return (0);
}

