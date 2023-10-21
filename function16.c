#include "main.h"

/**
 * _nocomment - function
 * @in: char
 * Return: char
 */
char *_nocomment(char *in)
{
	int i, j;

	j = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				j = i;
		}
	}
	if (j != 0)
	{
		in = _realloc(in, i, j + 1);
		in[j] = '\0';
	}
	return (in);
}

/**
 * _shloop - function
 * @datash: data_shell
 * Return: nothing
 */
void _shloop(shell_info *datash)
{
	int l, i;
	char *command;

	l = 1;
	while (l == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		command = _readline(&i);
		if (i != -1)
		{
			command = _nocomment(command);
			if (command == NULL)
				continue;
			if (error_ck(datash, command) == 1)
			{
				datash->s = 2;
				free(command);
				continue;
			}
			command = re_v(command, datash);
			l = split_commands(datash, command);
			datash->c += 1;
			free(command);
		}
		else
		{
			l = 0;
			free(command);
		}
	}
}

/*
 * error_not_found - function checks no error
 * @datash: shell_info
 * Return: char
*/
char *error_not_found(shell_info *datash)
{
	int len;
	char *err;
	char *str;

	str = _itoa(datash->c);
	len = _strlen(datash->argv[0]) + _strlen(str);
	len += _strlen(datash->argc[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, datash->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, datash->argc[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(str);
	return (err);
}

/**
 * error_exit_shell - function for error in exit
 * @datash: shell_info
 * Return: char
 */
char *error_exit_shell(shell_info *datash)
{
	int len;
	char *err;
	char *str;

	str = _itoa(datash->c);
	len = _strlen(datash->argv[0]) + _strlen(str);
	len += _strlen(datash->argc[0]) + _strlen(datash->argc[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(err, datash->argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, datash->argc[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->argc[1]);
	_strcat(err, "\n\0");
	free(str);
	return (err);
}
/**
 * _putchar - function to print.
 * @c: char.
 * Return: int
 */

int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, _numlen(c)));
}
