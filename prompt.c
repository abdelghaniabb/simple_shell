#include "main.h"

/**
 * main - check code
 * @argc: argc
 * @argv: argv
 * Return: int
 */
int main(int argc, char *argv[])
{
	char *user_input = NULL;
	size_t input_size = 0;
	int chars_read;

	if (argc >= 2)
	{
		printf("one argc\n");
	}
	while (1)
	{
		printf("%s", PROMPT);

		chars_read = getline(&user_input, &input_size, stdin);

		/*handle the "end of file" condition (ctr+D)*/
		if (chars_read == -1)
		{
			printf("\n ");
			/*free(user_input);*/
			exit(1);
		}

		/*remove newline char*/
		replace_char(user_input, '\n', '\0');

		/****************************/
		execute_command(user_input, argv[0]);

	}
/*	free(user_input);*/
	return (0);
}
