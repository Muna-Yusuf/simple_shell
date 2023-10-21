#include "main.h"

/**
 * _free - function that frees.
 * @infosh: struct.
 * Return: void.
 */
void _free(shell_info *infosh)
{
	unsigned int m;

	for (m = 0; infosh->_environ[m]; m++)
		free(infosh->_environ[m]);
	free(infosh->_environ);
	free(infosh->pid);
}

/**
 * commands_s - function to set data.
 * @infosh: struct.
 * @argv: char.
 * Return: void.
 */
void commands_s(shell_info infosh, char **argv)
{
	unsigned int m;

	infosh->argv = argv;
	infosh->command = NULL;
	infosh->argc = NULL;
	infosh->s = 0;
	infosh->c = 1;
	for (m = 0; environ[m]; m++)
	{
		infosh->_environ[m] = _strdup(environ[m]);
	}
	infosh->_environ[m] = NULL;
	infosh->pid = _itoa(getpid()); /*getpid not written in main.h?????????*/
}

/**
 * _strcat - function to concatenate 2 strings
 * @dest: string1
 * @src: string2
 * Return: string1
 */
char *_strcat(char *dest, char *src)
{
	int m, k;

	for (m = 0; dest[m] != '\0'; m++)
	;
	for (k = 0; src[k] != '\0'; k++)
	{
		dest[m] = src[k];
		m++;
	}
	dest[m] = '\0';
	return (dest);
}

/**
 * *_strcpy - function to copy string
 * @dest: string1
 * @src: string2
 * Return: string1
 */
char *_strcpy(char *dest, char *src)
{
	size_t x;

	for (x = 0; src[x] != '\0'; x++)
	{
		dest[x] = src[x];
	}
	dest[x] = '\0';
	return (dest);
}

/**
 * _strcmp - function to compare 2 strings
 * @str1: string1
 * @str2: string2
 * Return: 0 or 1
 */
int _strcmp(char *str1, char *str2)
{
	int m;

	for (m = 0; str1[m] == str2[m] && str1[m]; m++)
	;
	if (str1[m] > str2[m])
		return (1);
	if (str1[m] < str2[m])
		return (-1);
	return (0);
}
