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
