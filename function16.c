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
void _shloop(data_shell *datash)
{
	int l, i;
	char *in;

	l = 1;
	while (l == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		in = read_line(&i);
		if (i != -1)
		{
			in = without_comment(in);
			if (in == NULL)
				continue;
			if (check_syntax_error(datash, in) == 1)
			{
				datash->status = 2;
				free(in);
				continue;
			}
			in = rep_var(in, datash);
			l = split_commands(datash, in);
			datash->counter += 1;
			free(in);
		}
		else
		{
			l = 0;
			free(in);
		}
	}
}
