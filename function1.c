#include "main.h"


/**
 * _free - function that frees.
 * infosh: struct.
 * Return: void.
 */
void _free(shell_info infosh)
{
	unsigned int i;

	for (i = 0; infosh->_environ[i]; i++)
	{
		free(infosh->_environ[i]);
	}
	free(infosh->_environ);
	free(infosh->pid);
}

/**
 * commands_s - function to set data.
 * @infosh: struct.
 * @agrv: char.
 * Return: void.
 */
void commands_s(shell_info infosh, char **argv)
{
	unsigned int i;

	infosh->argv = argv;
	infosh->command = NULL;
	infosh->argc = NULL;
	infosh->s = 0;
	infosh->c = 1;

	for (i = 0; environ[i]; i++)
	{
		infosh->_environ[i] = _strdup(environ[i]);
	}
	infosh->_environ[i] = NULL;
	infosh->pid = _itoa(getpid()
	
}
