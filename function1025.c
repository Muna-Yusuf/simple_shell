#include "main.h"

/**
 * re_v - function thar retern char
 * @input: char.
 * @infosh: struct.
 * Return: char.
 */
char *re_v(char *input, shell_info *infosh)
{
	r_var *dot, *i;
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
		len2 += (i->length_value - indx->length);
		i = i->next;
	}
	len2 += len1;

	input2 = malloc(sizeof(char) * (len2 + 1));
	input2[len2] = '\0';
	input2 = replaced_input(&dot, input, input2, len2);

	free(input);
	free(s);
	free_rvar_list(&dot);/*function*/

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
		aux_help_general(); /* function 9999999999999999999999999999 */
	else if (_strcmp(infosh->argc[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(infosh->argc[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(infosh->argc[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(infosh->argc[1], "help") == 0)
		aux_help();
	else if (_strcmp(infosh->argc[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(infosh->argc[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(infosh->argc[1], "alias") == 0)
		aux_help_alias();
	else
		_putchar(infosh->argc[0],
		      _strlen(infosh->arg[0]));
	infosh->s = 0;
	return (1);
}
