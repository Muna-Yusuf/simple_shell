#include "main.h"

/**
 * _exec - function
 * @datash: of type data_shell
 * Return: 0 if executable or -1
 */
int _exec(data_shell *datash)
{
	struct stat st;
	int m;
	char *in;

	in = datash->args[0];
	for (m = 0; in[m]; m++)
	{
		if (in[m] == '.')
		{
			if (in[m + 1] == '.')
				return (0);
			if (in[m + 1] == '/')
				continue;
			else
				break;
		}
		else if (in[m] == '/' && m != 0)
		{
			if (in[m + 1] == '.')
				continue;
			m++;
			break;
		}
		else
			break;
	}
	if (m == 0)
		return (0);
	if (stat(in + m, &st) == 0)
		return (m);
	get_error(datash, 127);
	return (-1);
}

/**
 * _errcheck - function to check error cmd
 * @d: char
 * @datash: of type data_shell
 * Return: 0 or 1
 */
int _errcheck(char *d, data_shell *datash)
{
	if (d == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			get_error(datash, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * _execute - function to execute cmd
 * @datash: of type data_shell
 * Return: 1
 */
int _execute(data_shell *datash)
{
	pid_t p;
	pid_t w;
	int st;
	int ex;
	char *d;

	ex = exec(datash);
	if (ex == -1)
		return (1);
	if (ex == 0)
	{
		d = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(d, datash) == 1)
			return (1);
	}
	p = fork();
	if (p == 0)
	{
		if (ex == 0)
			d = _which(datash->args[0], datash->_environ);
		else
			d = datash->args[0];
		execve(d + ex, datash->args, datash->_environ);
	}
	else if (p < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			w = waitpid(p, &st, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(st));
	}
	datash->status = st / 256;
	return (1);
}

/**
 * _exit - function to exit the shell
 * @datash: of type data_shell
 * Return: 0 or 1
 */
int _exit(data_shell *datash)
{
	unsigned int st;
	int d;
	int len;
	int num;

	if (datash->args[1] != NULL)
	{
		st = _atoi(datash->args[1]);
		d = check_digit(datash->args[1]);
		len = _strlen(datash->args[1]);
		num = st > (unsigned int)INT_MAX;
		if (!d || len > 10 || num)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (st % 256);
	}
	return (0);
}

/**
 * _readline - function to read line
 * @x: int
 * Return: char
 */
char *_readline(int *x)
{
	char *in = NULL;
	size_t size = 0;

	*x = getline(&in, &size, stdin);
	return (in);
}
