#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
  * get_commande - get line from stdin
  * @buffer: buffer
  * @size: buffer size
  * Return: length
  */
int get_commande(char *buffer, size_t *size)
{
	int len = 0;

	len = getline(&buffer, size, stdin);
	if (len == -1)
		exit(1);
	buffer[len - 1] = '\0';

	return (len);
}
/**
  * execute_commande - execve
  * @command: command t oexecute
  * Return: -1 if fail
  */
int execute_commande(char *command)
{
	char *arg[2];
	int len;

	len = execve(arg[0], arg, NULL)
	arg[0] = command;
	arg[1] = NULL;
	if (execve(arg[0], arg, NULL) == -1)
		exit(1);
	return (len);
}

/**
 * main - check code
 * @argc: argc
 * @argv: argv
 * Return: int
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *buffer = NULL;
	size_t buffer_size = 1024;
	pid_t pid;
	int status;

	buffer = (char *) malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		exit(1);
	if (!isatty(0))
	{
		get_commande(buffer, &buffer_size);
		if (execute_commande(buffer) == -1)
			perror(argv[0]), exit(1);
	}
	while (1)
	{
		printf("#cisfun$ ");
		if (get_commande(buffer, &buffer_size) == -1)
			return (-1);
		if (strcmp(buffer, "exit") == 0)
			break;
		pid = fork();
		if (pid < 0)
		{
			free(buffer);
			perror(argv[0]);
			exit(1);
		}
		else if (pid == 0)
		{
			if (execute_commande(buffer) == -1)
			{
				perror(argv[0]);
				exit(1);
			}
		}
		else
			wait(&status);
	}
	return (0);
}

