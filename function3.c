#include "main.h"

/**
 * _strtok - function to split string
 * @commands: char
 * @delim: delimiter
 * Return: char
 */
char *_strtok(char commands[], const char *delim)
{
	static char *s, *end;
	char *start;
	unsigned int m, bool;

	if (commands != NULL)
	{
		if (cmp_chars(commands, delim))
			return (NULL);
		s = commands;
		m = _strlen(commands);
		end = &commands[m];
	}
	start = s;
	if (start == end)
		return (NULL);
	for (bool = 0; *s; s++)
	{
		if (s != start)
			if (*s && *(s - 1) == '\0')
				break;
		for (m = 0; delim[m]; m++)
		{
			if (*s == delim[m])
			{
				*s = '\0';
				if (s == start)
					start++;
				break;
			}
		}
		if (bool == 0 && *s)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (start);
}

/**
 * check_digit - function to check if digit or not
 * @s: char
 * Return: 0 or 1
 */
int check_digit(const char *s)
{
	unsigned int m;

	for (m = 0; s[m]; m++)
	{
		if (s[m] < 48 || s[m] > 57)
			return (0);
	}
	return (1);
}

/**
 * _strrev - function to reverse a string
 * @s: string
 * Return: nothing
 */
void _strrev(char *s)
{
	int c = 0, m, k;
	char *str, temp;

	while (c >= 0)
	{
		if (s[c] == '\0')
			break;
		c++;
	}
	str = s;
	for (m = 0; m < (c - 1); m++)
	{
		for (k = m + 1; k > 0; k--)
		{
			tmp = *(str + k);
			*(str + k) = *(str + (k - 1));
			*(str + (k - 1)) = tmp;
		}
	}
}

/**
 * _itoa - function to convert integer to string
 * @n: integer
 * Return: string converted from integer
 */
char *_itoa(int n)
{
	unsigned int m;
	int len = get_len(n);
	char *b;

	b = malloc(sizeof(char) * (len + 1));
	if (b == 0)
		return (NULL);
	*(b + len) = '\0';
	if (n < 0)
	{
		m = n * -1;
		b[0] = '-';
	}
	else
		m = n;
	len--;
	do {
		*(b + len) = (m % 10) + '0';
		m /= 10;
		len--;
	}
	while (m > 0)
	;
	return (b);
}

/**
 * _atoi - finction to convert string to integer
 * @s: string to be converted
 * Return: integer converted
 */
int _atoi(char *s)
{
	unsigned int c = 0, size = 0, k = 0, p = 1, m = 1, i;

	while (*(s + c) != '\0')
	{
		if (size > 0 && (*(s + c) < '0' || *(s + c) > '9'))
			break;
		if (*(s + c) == '-')
			p *= -1;
		if ((*(s + c) >= '0') && (*(s + c) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		c++;
	}
	for (i = c - size; i < c; i++)
	{
		k = k + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (k * p);
}
