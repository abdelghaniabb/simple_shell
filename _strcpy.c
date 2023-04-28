/**
  * _strcpy - copy string from src to dest
  * @src: source string
  * @dest: dest memory
  * Return: pointer to dest
  */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}
