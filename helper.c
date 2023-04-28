/**
 * is_whitespace -check if there only space
 * @c: the string
 * Return: 1 or 0
 */
int is_whitespace(char *c)
{
	int i;
	char s;

	for (i = 0; c[i] != '\0'; i++)
	{
		s = c[i];
		if (s != '\t' && s != ' ')
			return (0);
	}
	return (1);
}
/**
 * make_tokens - make tokens
 * @string: string pointer
 * Return: char
 */
char **make_tokens(char *string)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = (char **)malloc(sizeof(char) * 1024);
	if (tokens == NULL)
	{
		exit(1);
	}
	token = strtok(string, "\n\t\r ");
	if (token == NULL)
		return (NULL);
	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, "\n\t\r ");
	}
	tokens[i] = NULL;

	return (tokens);
}
/**
 * _EOF - buffer is EOF
 * @buffer: string.
 * Return: void
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(0);
}
