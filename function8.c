#include "main.h"

/**
 * env_comp - function that prints env.
 * @xenv: char.
 * @name: char.
 * Return: int.
 */

int env_comp(const char *xenv, const char *name)
{
	int x;

	for (x = 0; xenv[x] != '='; x++)
	{
		if (xenv[x] != name[x])
		{
			return (0);
		}
	}
	return (x + 1);
}

/**
 * _getenv - function getenv.
 * @commands: char.
 * @_environ: char.
 * Return: char.
 */

char *_getenv(const char *commands, char **_environ)
{
	char *env_int = NULL;
	int x, y = 0;

	for (x = 0; _environ[x]; x++)
	{
		y = env_comp(_environ[x], commands);
		if (y)
		{
			env_int = _environ[x];
			break;
		}
	}
	return (env_int + y);
}

/**
 * int_env_command - function prints env.
 * @infosh: strcut.
 * Return: int.
 */
int int_env_command(shell_info *infosh)
{
	int x, y;

	for (x = 0; infosh->_environ[x]; x++)
	{
		for (y = 0; infosh->_environ[x][y]; y++)
			;
		_putchar(infosh->_environ[x]);
		_putchar("\n");
	}
	infosh->s = 0;
	return (1);
}

/**
 * info - function info.
 * @name: char.
 * @value: char.
 * Return: char.
 */
char *info(char *name, char *value)
{
	char *command;
	int name_len, value_len, len;

	name_len = _strlen(name);
	value_len = _strlen(value);
	len = name_len + value_len + 2;
	command = malloc(sizeof(char) * (len));
	_strcpy(command, name);
	_strcpy(command, "=");
	_strcpy(command, value);
	_strcpy(command, "\0");
	return (new);
}

/**
 * set_env - function set_env.
 * @command: char.
 * @value: char.
 * @infosh: struct.
 *
 * Return: void.
 */

void set_env(char *command, char *value, shell_info *infosh)
{
	int x;
	char *env1, *env2;

	for (x = 0; infosh->_environ[x]; x++)
	{
		env1 = _strdup(infosh->_environ[x]);
		env2 = _strtok(env1, "=");
		if (_strcmp(env2, command) == 0)
		{
			free(infosh->_environ[x]);
			infosh->_environ[x] = info(env2, value);
			free(env1);
			return;
		}
		free(env1);
	}

	infosh->_environ = _reallocdp(infosh->_environ, x, sizeof(char *) * (x + 2)); /* function */
	infosh->_environ[x] = info(command, value);
	infosh->_environ[x + 1] = NULL;
}

