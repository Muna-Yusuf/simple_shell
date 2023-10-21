#include "main.h"

/**
 * _strchr - function
 * @s: character
 * @c: character
 * Return: char
 */
char *_strchr(char *s, char c)
{
	unsigned int m;

	for (m = 0; *(s + m) != '\0'; m++)
		if (*(s + m) == c)
			return (s + m);
	if (*(s + m) == c)
		return (s + m);
	return ('\0');
}

/**
 * _strspn - function
 * @s: char
 * @accept: char
 * Return: int
 */
int _strspn(char *s, char *accept)
{
	int m, k, bool;

	for (m = 0; *(s + m) != '\0'; m++)
	{
		bool = 1;
		for (k = 0; *(accept + k) != '\0'; k++)
		{
			if (*(s + m) == *(accept + k))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (m);
}

/**
 * _strdup - function to duplicate
 * @str: char
 * Return: char
 */
char *_strdup(const char *str)
{
	char *x;
	size_t len;

	len = _strlen(str);
	x = malloc(sizeof(char) * (len + 1));
	if (x == NULL)
		return (NULL);
	_memcpy(x, str, len + 1);
	return (x);
}

/**
 * _strlen - function to find length of string
 * @s: string
 * Return: length
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	;
	return (len);
}
