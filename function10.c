#include "main.h"

/**
 * envir_error - function that get error
 * @infosh: struct.
 * Return: char
 */
char *envir_error(shell_info *infosh)
{
	int len;
	char *error_co, *value, *m;

	value = itoa(infosh->c);
	m = ": Unable to add/remove from environment\n";
	len = _strlen(infosh->argv[0]) + _strlen(value);
	len += _strlen(infosh->argc[0]) + _strlen(m) + 4;
	error_co = malloc(sizeof(char) * (len + 1));
	if (error_co == 0)
	{
		free(error_co);
		free(value);
		return (NULL);
	}

	_strcpy(error_co, infosh->agrv[0]);
	_strcat(error_co, ": ");
	_strcat(error_co, value);
	_strcat(error_co, ": ");
	_strcat(error_co, infosh->argc[0]);
	_strcat(error_co, m);
	_strcat(error_co, "\0");
	free(value);
	return (error_co);
}
/**
 * error_126 - function gets error
 * @infosh: struct
 * Return: char.
 */
char *error_126(shell_info *infosh)
{
	int len;
	char *value, *error_co;

	value = _itoa(infosh->c);
	len = _strlen(infosh->argv[0]) + _strlen(value);
	len += _strlen(infosh->argc[0]) + 24;
	error_co = malloc(sizeof(char) * (len + 1));
	if (error_co == 0)
	{
		free(error_co);
		free(value);
		return (NULL);
	}
	_strcpy(error_co, infosh->argv[0]);
	_strcat(error_co, ": ");
	_strcat(error_co, value);
	_strcat(error_co, ": ");
	_strcat(error_co, infosh->argc[0]);
	_strcat(error_co, ": Permission denied\n");
	_strcat(error_co, "\0");
	free(value);
	return (error_co);
}

/**
 * _enviro_check - function that checks.
 * @dot: struct
 * @i: int.
 * @infosh: struct.
 * Return: void.
 */
void _enviro_check(command_var_r **dot, char *i, shell_info *infosh)
{
	int r, c, j, l;
	char **_enviro_b;

	_enviro_b = infosh->_environ;
	for (r = 0; _enviro_b[r]; r++)
	{
		for (j = 1, c = 0; _enviro[r][c]; c++)
		{
			if (_enviro_b[r][c] == '=')
			{
				l = _strlen(_enviro_b[r] + c + 1);
				add_rvar_node(dot, j, _enviro_b[r] + c + 1, l); /* function */
				return;
			}

			if (i[j] == _enviro_b[r][c])
				j++;
			else
				break;
		}
	}

	for (j = 0; i[j]; j++)
	{
		if (i[j] == ' ' || i[j] == '\t' || i[j] == ';' || i[j] == '\n')
			break;
	}

	add_rvar_node(dot, j, NULL, 0); /* function */
}

/**
 * _vars_ch - function checks
 * @dot: struct
 * @x: char
 * @str: char
 * @infosh: struct
 * Return: int.
 */
int _vars_ch(command_var_r **dot, char *x, char *str, shell_info *infosh)
{
	int i, list, d;

	list = _strlen(srt);
	d = _strlen(infosh->pid);

	for (i = 0; x[i]; i++)
	{
		if (x[i] == '$')
		{
			if (x[i + 1] == '?')
				add_rvar_node(dot, 2, srt, list), i++;
			else if (x[i + 1] == '$')
				add_rvar_node(dot, 2, infosh->pid, d), i++;
			else if (x[i + 1] == '\n')
				add_rvar_node(dot, 0, NULL, 0);
			else if (x[i + 1] == '\0')
				add_rvar_node(dot, 0, NULL, 0);
			else if (x[i + 1] == ' ')
				add_rvar_node(dot, 0, NULL, 0);
			else if (x[i + 1] == '\t')
				add_rvar_node(dot, 0, NULL, 0);
			else if (x[i + 1] == ';')
				add_rvar_node(dot, 0, NULL, 0);
			else
				_enviro_check(dot, x + i, infosh);
		}
	}

	return (i);
}

/**
 * _replaced - function that replaced.
 * @dot: struct.
 * @input: char.
 * @input2: char.
 * @length: int.
 * Return: char.
 */
char *_replaced(command_var_r **dot, char *input, char *input2, int length)
{
	r_var *dot_in;
	int x, y, z; /* i, j, k */

	dot_in = *dot;
	for (y = x = 0; x < length; x++)
	{
		if (input[y] == '$')
		{
			if (!(dot_in->length) && !(dot_in->length_value))
			{
				input2[x] = input[y];
				y++;
			}
			else if (dot_in->length && !(dot_in->length_value))
			{
				for (z = 0; z < dot_in->length; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < dot_in->length_value; z++)
				{
					new_input[x] = dot_in->value[z];
					x++;
				}
				y += (dot_in->length);
				x--;
			}
			dot_in = dot_in->next;
		}
		else
		{
			input2[x] = input[y];
			y++;
		}
	}

	return (input2);
}
