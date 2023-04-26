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
		perror("Error memory allocation");
		exit(1);
	}
	len_cmd = getline(&buffer, &buffer_size, stdin);

	if (len_cmd == -1)
	{
		exit(1);
	}
	buffer[len_cmd - 1] = '\0';

	return (buffer);
}
/**
  * execute_cmd - execute cmd
  * @command: command
  * @argv: args
  */
void execute_cmd(char *command, char *argv[])
{
	pid_t pid;
	char *list[2];

	pid = fork();

	if (pid == -1)
	{
		perror("error");
		exit(1);
	}
	if (pid == 0)
	{
		list[0] = command;
		list[1] = NULL;
		if (execve(list[0], list, NULL) == -1)
		{
			perror(argv[0]);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		printf("\n");
	}
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

	while (1)
	{
		if (isatty(0))
			printf("$ ");
		command = get_cmd();
		if (strcmp(command, "exit") == 0)
			break;
		execute_cmd(command, argv);
	}
	free(command);
	return (0);
}
