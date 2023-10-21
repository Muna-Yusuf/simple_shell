#include "main.h"

/**
 * _realloc - function that reallocate
 * @ptr: pointer
 * @size: unsigned int
 * @newsize: unsigned int
 * Return: nothing
 */
void *_realloc(void *ptr, unsigned int size, unsigned int newsize)
{
	void *nptr;

	if (ptr == NULL)
		return (malloc(newsize));
	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (newsize == size)
		return (ptr);
	nptr = malloc(newsize);
	if (nptr == NULL)
		return (NULL);
	if (newsize < size)
		_memcpy(nptr, ptr, newsize);
	else
		_memcpy(nptr, ptr, size);
	free(ptr);
	return (nptr);
}

/**
 * _reallocdup - function
 * @ptr: pointer
 * @size: unsigned int
 * @newsize: unsigned int
 * Return: new pointer
 */
char **_reallocdup(char **ptr, unsigned int size, unsigned int newsize)
{
	char **nptr;
	unsigned int m;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * newsize));
	if (newsize == size)
		return (ptr);
	nptr = malloc(sizeof(char *) * newsize);
	if (nptr == NULL)
		return (NULL);
	for (m = 0; m < size; m++)
		nptr[m] = ptr[m];
	free(ptr);
	return (nptr);
}

/**
 * _help - function
 * Return: nothing
 */
void _help(void)
{
	char *x = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, x, _strlen(x));
	x = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, x, _strlen(x));
	x = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, x, _strlen(x));
}

/**
 * _helpalias - function
 * Return: nothing
 */
void _helpalias(void)
{
	char *x = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, x, _strlen(x));
	x = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, x, _strlen(x));
}

/**
 * _helpcd - function
 * Return: nothing
 */
void _helpcd(void)
{
	char *x = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, x, _strlen(x));
	x = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, x, _strlen(x));
}
