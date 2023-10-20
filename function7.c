#include "main.h"
/**
 * char_rep - function that returns repeated char.
 * @command: char.
 * @x: int.
 * Return: int.
 */

int char_rep(char *command, int x)
{
	if (*(command - 1) == *x)
	{
		return (char_rep(command - 1, i + 1));
	}
	return (i);
}

/**
 * sep_err - function that show error.
 * @command: char.
 * @x: int.
 * @com_l: char.
 * Return: int
 */
int sep_err(char *command, int x, char com_l)
{
	int i;

	i = 0;
	if (*command == '\0')
		return (0);
	if (*command == ' ' || *command == '\t')
	{
		return (sep_err(command + 1, x + 1, com_l));
	}
	if (*command == ';')
		if (com_l == '|' || com_l == '&' || com_l == ';')
			return (x);

	if (*command == '|')
	{
		if (com_l == ';' || com_l == '&')
			return (x);
		if (com_l == '|')
		{
			i = sep_err(command, 0);
			if (i == 0 || i > 1)
			{
				return (x);
			}
		}
	}
	if (*command == '&')
	{
		if (com_l == ';' || com_l == '|')
			return (x);
		if (com_l == '&')
		{
			i = sep_err(command, 0);
			if (i == 0 || i > 1)
				return (i);
		}
	}
	return (sep_err(command + 1, x + 1, *command));
}

/**
 * char_f - function that retuern int.
 * @command: char.
 * @x: int.
 * Return: int.
 */

int char_f(char *command, int *x)
{
	for (*x = 0; command[*x]; *x += 1)
	{
		if (command[*x] == ' ' || command[*x] == '\t')
		{
			continue;
		}
		if (command[*x] == ';' || command[*x] == '|' || command[*x] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * error_print - function that print error.
 * @infosh: struct.
 * @command: char.
 * @x: int.
 * @bool: int.
 * Return: void.
 */

void error_print(shell_info *infosh, char *command, int x, int bool)
{
	char *m1, *m2, *m3, *m_error, *c;
	int l;

	if (command[x] == ';')
	{
		if (bool == 0)
		{
			m1 = (command[x + 1] == ';' ? ";;" : ";");
		}
		else
			m1 = (command[x - 1] == ';' ? ";;" : ";");
	}
	if (command[x] == '|')
		m1 = (command[x + 1] == '|' ? "||" : "|");
	if (command[x] == '&')
		m1 = (command[x + 1] == '&' ? "&&" : "&");
	m2 = ": Syntax error: \"";
	m3 = "\"unexpected\n";
	c = _itoa(infosh->c);
	l = _strlen(infosh->argv[0] + _strlen(c)); /* argv or argc */
	l += _strlen(m1) + _strlen(m2) + _strlen(m3) + 2;

	m_error = malloc(sizeof(char) * (length + 1));
	if (m_error == 0)
	{
		free(c);
		return;
	}
	_strcpy(m_error, infosh->argv[0]);
	_strcpy(m_error, ": ");
	_strcpy(m_error, c);
	_strcpy(m_error, m2);
	_strcpy(m_error, m1);
	_strcpy(m_error, m3);
	_strcpy(m_error, "\0");
	write(STDERR_FILENO, m_error, l);
	free(m_error);
	free(c);
}

/**
 * error_ck - function that check errors.
 * @infosh: struct.
 * @command: char.
 *
 * Return: int.
 */
int error_ck(shell_info *infosh, char *command)
{
	int x = 0, y = 0, z = 0;

	y = char_f(command, &x);
	if (y == -1)
	{
		error_print(infosh, command, x, 0)
		return (1);
	}
	z = sep_err(command + x, 0, *(command + x));
	if (z != 0)
	{
		error_print(infosh, command, x + z, 1);
		return (1);
	}
	return (0);
}
