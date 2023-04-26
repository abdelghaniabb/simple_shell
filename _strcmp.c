/**
  * _strcmp - compare 2 str
  * @str1: first string
  * @str2: second string
  * Return: -1 1 0
  */

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


