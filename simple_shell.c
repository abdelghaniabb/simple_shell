#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
  * get_cmd - get command
  * Return: buffer
  */
char *get_cmd(void)
{
	size_t buffer_size = 256;
	char *buffer = (char *) malloc(buffer_size * sizeof(char));
	int len_cmd;

	if (buffer == NULL)
	{
		perror("Error:");
		return (NULL);
	}
	len_cmd = getline(&buffer, &buffer_size, stdin);
	if (len_cmd == -1)
	{
		free(buffer);
		exit(1);
	}
	buffer[len_cmd - 1] = '\0';

	return (buffer);
}
/**
  * execute_cmd - execute cmd
  * @command: command
  * @argv: args
  * Retunr: 1 success -1 fail
  */
int execute_cmd(char *command, char *argv[])
{
	pid_t pid;
	char *list[2];
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	if (pid == 0)
	{
		list[0] = command;
		list[1] = NULL;
		if (execve(list[0], list, NULL) == -1)
		{
			perror(argv[0]);
			return (-1);
		}
	}
	else
	{
		wait(&status);
		if (status == -1)
		{
			perror("Error:");
			return (-1);
		}
	}
	return (1);
}

/**
 * main - check code
 * @argc: argc
 * @argv: argv
 * Return: int
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *command;
	int exec_s;
	while (1)
	{
		if (isatty(0))
			printf("$ ");
		command = get_cmd();
		if (command == NULL)
			return (1);
		if (strcmp(command, "exit") == 0)
			break;

		exec_s = execute_cmd(command, argv);
		if (exec_s == -1)
		{
			free(command);
			return (1);
		}
	}
	free(command);
	return (0);
}
