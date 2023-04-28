/**
  * _strcmp - compare 2 str
  * @s1: first string
  * @s2: second string
  * Return: -1 1 0
  */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s1[i] == s2[i]; i++)
	{
	}
	return (s1[i] - s2[i]);
}
