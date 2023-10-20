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

void error_print(shell_info *infosh, )
