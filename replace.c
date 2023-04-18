#include <string.h>

size_t replace_char(char *str, char old_char, char new_char)
{
	size_t count = 0;
	size_t i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == old_char)
			str[i] = new_char;
		count++;
	}
	return (count);
}
