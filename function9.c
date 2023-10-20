#include "main.h"

/**
 * _setenv - function setenv.
 * @infosh: struct.
 *
 * Return: int
 */
int _setenv(shell_info *infosh)
{

	if (infosh->argc[1] == NULL || infosh->argc[2] == NULL)
	{
		get_error(infosh, -1);
		return (1);
	}
	set_env(infosh->argc[1], infosh->argc[2], infosh);
	return (1);
}

/**
 * _unsetenv - function unsetenv.
 * @infosh: struct.
 * Return: int.
 */
int _unsetenv(shell_info *infosh)
{
	char **env_re;
	char *value, *name;
	int x, y, z = -1;

	if (infosh->argc[1] == NULL)
	{
		get_error(infosh, -1);
		return (1);
	}
	for (x = 0; infosh->_environ[x]; x++)
	{
		value = _strdup(infosh->_environ[i]);
		name = _strtok(varlue, "=");
		if (_strcmp(name, infosh->argc[1]) == 0)
		{
			z = i;
		}
		free(value);
	}
	if (z == -1)
	{
		get_error(infosh, -1);
		return (1);
	}
	env_re = malloc(sizeof(char *) * (x));
	for (x = y = 0; infosh->_environ[x]; x++)
	{
		if (x != z)
		{
			env_re[y] = infosh->_environ[x];
			y++;
		}
	}
	env_re[y] = NULL;
	free(infosh->_environ[z]);
	free(infosh->_environ);
	infosh->_environ = env_re
	return (1);
}

/**
 * get_error - function gets error.
 * @infosh: struct.
 * @l: int.
 * Return: int.
 */
int get_error(shell_info *infosh, int l)
{
	char *error_co

	switch (l)
	{
	case -1:
		error_co = envir_error(infosh);
		break;
	case 126:
		error_co = error_126(infosh);
		break;
	case 127:
		error_co = error_not(datash); /* function */
		break;
	case 2:
		if (_strcmp("exit", infosh->argc[0]) == 0)
			error_co = error_exit(infosh); /* function */
		else if (_strcmp("cd", infosh->argc[0]) == 0)
			error = error_cd(infosh);
		break;
	}

	if (error_co)
	{
		write(STDERR_FILENO, error_co, _strlen(error_co));
		free(error_co);
	}

	infosh->s = l;
	return (l);
}

/**
 * _cd_str - function to cd .
 * @infosh: struct
 * @m: char.
 * @error_co: char.
 * @value: char.
 * Return: char.
 */
char *_cd_str(shell_info *infosh, char *m, char *error_co, char *value)
{
	char *flag;

	_strcpy(error_co, infosh->argv[0]);
	_strcat(error_co, ": ");
	_strcat(error_co, value);
	_strcat(error_co, ": ");
	_strcat(error_co, infosh->argc[0]);
	_strcat(error_co, m);
	if (infosh->argc[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = datash->args[1][1];
		flag[2] = '\0';
		_strcat(error_co, flag);
		free(flag);
	}
	else
	{
		_strcat(error_co, infosh->argc[1]);
	}

	_strcat(error_co, "\n");
	_strcat(error_co, "\0");
	return (error_co);
}

/**
 * error_cd - function to print error.
 * @infosh: struct.
 * Return: char.
 */
char *error_cd(shell_info *infosh)
{
	int len, _len;
	char *error_co, *value, *m;

	value = _itoa(infosh->c);
	if (infosh->argc[1][0] == '-')
	{
		m = ": Illegal option ";
		_len = 2;
	}
	else
	{
		m = ": can't cd to ";
		_len = _strlen(infosh->argc[1]);
	}

	len = _strlen(infosh->argv[0]) + _strlen(infosh->argc[0]);
	len += _strlen(value) + _strlen(m) + _len + 5;
	error_co = malloc(sizeof(char) * (len + 1));

	if (error_co == 0)
	{
		free(value);
		return (NULL);
	}

	error_co = _cd_str(infosh, m, error_co, value);

	free(value);

	return (error_co);
}
