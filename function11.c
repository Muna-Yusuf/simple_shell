#include "main.h"

/**
 * _exec - function
 * @infosh: of type data_shell
 * Return: 0 if executable or -1
 */
int _exec(shell_info *infosh)
{
	struct stat st;
	int m;
	char *in;

	in = infosh->argc[0];
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
	get_error(infosh, 127);
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
 * @infosh: of type data_shell
 * Return: 1
 */
int _execute(shell_info *infosh)
{
	pid_t p;
	pid_t w;
	int st;
	int ex;
	char *d;

	ex = _exec(infosh);
	if (ex == -1)
		return (1);
	if (ex == 0)
	{
		d = _which(infosh->argc[0], infosh->_environ);
		if (_errcheck(d, infosh) == 1)
			return (1);
	}
	p = fork();
	if (p == 0)
	{
		if (ex == 0)
			d = _which(infosh->argc[0], infosh->_environ);
		else
			d = infosh->argc[0];
		execve(d + ex, infosh->argc, infosh->_environ);
	}
	else if (p < 0)
	{
		perror(infosh->argv[0]);
		return (1);
	}
	else
	{
		do {
			w = waitpid(p, &st, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(st));
	}
	infosh->s = st / 256;
	return (1);
}

/**
 * _exit - function to exit the shell
 * @infosh: of type data_shell
 * Return: 0 or 1
 */
int _exit(shell_info *infosh)
{
	unsigned int st;
	int d;
	int len;
	int num;

	if (infosh->argc[1] != NULL)
	{
		st = _atoi(infosh->argc[1]);
		d = check_digit(infosh->argc[1]);
		len = _strlen(infosh->argc[1]);
		num = st > (unsigned int)INT_MAX;
		if (!d || len > 10 || num)
		{
			get_error(infosh, 2);
			infosh->s = 2;
			return (1);
		}
		infosh->s = (st % 256);
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
