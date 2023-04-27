/**
  * _strcmp - compare 2 str
  * @s1: first string
  * @s2: second string
  * Return: -1 1 0
  */

int _strcmp(char *s1, char *s2)
{
	unsigned int i = 0;

	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}

	return (1);
}
