#include "main.h"
#define PROMPT "$ "
/**
  * main - entry point to shell
  * Return: error codes
  */
int main(void)
{
	char *user_input = NULL;
	size_t input_size = 0;
	size_t chars_read;

	while (1)
	{
		printf(PROMPT);

		chars_read = getline(&user_input, &input_size, stdin);

		/*handle the "end of file" condition (ctr+D)*/
		if (chars_read == -1)
		{
			printf("\n ");
			free(user_input);
			exit(0);
		}

		/*remove newline char*/
		replace_char(user_input, '\n', '\0');

		/****************************/
		execute_command(user_input);
	}
	free(user_input);
	return (0);
}
