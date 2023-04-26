#include "main.h"


int _strcmp(char str1[], char str2[])
{
	int i = 0;

	while (str1[i] != '\0' && str1[i] == str2[i])
	{
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
	{
		return (0);
	}
	else if (str1[i] < str2[i])
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

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
		return (NULL);
	}
	len_cmd = getline(&buffer, &buffer_size, stdin);
	if (len_cmd == -1)
	{
		free(buffer);
		exit(127);
	}
	buffer[len_cmd - 1] = '\0';

	return (buffer);
}
/**
  * execute_cmd - execute cmd
  * @command: command
  * @argv: args
  * Return: 1 success -1 fail
  */
int execute_cmd(char *command, char *argv[])
{
	pid_t pid;
	char *list[2];
	int status;

	pid = fork();

	if (pid == -1)
	{
		free(command);
		return (-1);
	}
	if (pid == 0)
	{
		list[0] = command;
		list[1] = NULL;
		if (execve(list[0], list, NULL) == -1)
		{
			perror(argv[0]);
			free(command);
			return (127);
		}
	}
	else
	{
		wait(&status);
		if (status == -1)
		{
			free(command);
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

	while (1)
	{
		if (isatty(0))
			printf("$ ");
		command = get_cmd();
		if (command == NULL)
			return (1);
		if (_strcmp(command, "exit") == 0)
			exit(0);

		execute_cmd(command, argv);
	}
	free(command);
	return (0);
}
