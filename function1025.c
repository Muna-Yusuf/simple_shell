#include "main.h"

/**
 * re_v - function thar retern char
 * @input: char.
 * @infosh: struct.
 * Return: char.
 */
char *re_v(char *input, shell_info *infosh)
{
	command_var_r *dot, *i;
	char *s, *input2;
	int len1, len2;

	s = _itoa(infosh->s);
	dot = NULL;
	len1 = _vars_ch(&dot, input, s, infosh);
	if (dot == NULL)
	{
		free(s);
		return (input);
	}
	i = dot;
	len2 = 0;
	while (i != NULL)
	{
		len2 += (i->length_value - i->length);
		i = i->next;
	}
	len2 += len1;
	input2 = malloc(sizeof(char) * (len2 + 1));
	input2[len2] = '\0';
	input2 = _replaced(&dot, input, input2, len2);
	free(input);
	free(s);
	_freervar(&dot);
	return (input2);
}

/**
 * _helper - function helpre.
 * @infosh: struct.
 * Return: int.
*/
int _helper(shell_info *infosh)
{

	if (infosh->argc[1] == 0)
		_helpgeneral();
	else if (_strcmp(infosh->argc[1], "setenv") == 0)
		_helpsetenv();
	else if (_strcmp(infosh->argc[1], "env") == 0)
		_helpenv();
	else if (_strcmp(infosh->argc[1], "unsetenv") == 0)
		_helpunsetenv();
	else if (_strcmp(infosh->argc[1], "help") == 0)
		_help();
	else if (_strcmp(infosh->argc[1], "exit") == 0)
		_helpexit();
	else if (_strcmp(infosh->argc[1], "cd") == 0)
		_helpcd();
	else if (_strcmp(infosh->argc[1], "alias") == 0)
		_helpalias();
	else
	{
		write(STDERR_FILENO, infosh->argc[0],_strlen(infosh->argc[0]));
	}
	infosh->s = 0;
	return (1);
}
