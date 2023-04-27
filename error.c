#include "main.h"
/**
 * error - A function that prints message not found.
 * @name: The name of the shell.
 * @counter: Number of cicles.
 * @command: The pointer to tokenized command.
 */
void error(char *name, int counter, char *command)
{
	char c;

	c = counter + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command, _strlen(command));
	write(STDOUT_FILENO, ": not found\n", 12);
}

/**
 * _strlen - A function that finds the length of the string
 * @s: The input string
 * Return: The length of the string
 */
unsigned int _strlen(char *s)
{
	unsigned int len = 0;

	while (s[len])
		len++;

	return (len);
}
