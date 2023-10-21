#include "main.h"

/**
 * _numlen - function to find length of a number
 * @num: the number given
 * Return: length
 */
int _numlen(int num)
{
	unsigned int n;
	int len = 1;

	if (num < 0)
	{
		len++;
		n = num * -1;
	}
	else
		n = num;
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * swapping - function to swap
 * @input: char
 * @bool: int
 * Return: char
 */
char *swapping(char *input, int bool)
{
	int m;

	if (bool == 0)
	{
		for (m = 0; input[m]; m++)
		{
			if (input[m] == '|')
			{
				if (input[m + 1] != '|')
					input[m] = 16;
				else
					m++;
			}
			if (input[m] == '&')
			{
				if (input[m + 1] != '&')
					input[m] = 12;
				else
					m++;
			}
		}
	}
	else
	{
		for (m = 0; input[m]; m++)
		{
			input[m] = (input[m] == 16 ? '|' : input[m]);
			input[m] = (input[m] == 12 ? '&' : input[m]);
		}
	}
	return (input);
}

/**
 * _node_add - function to add nodes
 * @head_s: of type sep_list
 * @head_l: of type line_list
 * @command: char
 * Return: nothing
 */
void _node_add(list_s **head_s, command_list_s **head_l, char *command)
{
	int m;
	char *l;

	command = swapping(command, 0);
	for (m = 0; command[m]; m++)
	{
		if (command[m] == ';')
			_sepend(head_s, command[m]);
		if (command[m] == '|' || command[m] == '&')
		{
			_sepend(head_s, command[m]);
			m++;
		}
	}
	l = _strtok(command, ";|&");
	do {
		l = swapping(l, 1);
		_lineend(head_l, l);
		l = _strtok(NULL, ";|&");
	} while (l != NULL);
}

/**
 * _node_next - function to go to the next node
 * @lists: of type sep_list
 * @listl: of type line_list
 * @infosh: of type data_shell
 * Return: nothing
 */
void _node_next(list_s **lists, command_list_s **listl, shell_info *infosh)
{
	int m;
	list_s *sm;
	command_list_s *l;

	m = 1;
	sm = *lists;
	l = *listl;
	while (sm != NULL && m)
	{
		if (infosh->s == 0)
		{
			if (sm->sep == '&' || sm->sep == ';')
				m = 0;
			if (sm->sep == '|')
				l = l->next, sm = sm->next;
		}
		else
		{
			if (sm->sep == '|' || sm->sep == ';')
				m = 0;
			if (sm->sep == '&')
				l = l->next, sm = sm->next;
		}
		if (sm != NULL && !m)
			sm = sm->next;
	}
	*lists = sm;
	*listl = l;
}

/**
 * token_command - function to tokenize commands
 * @datash: of type data_shell
 * @input: char
 * Return: 0 or 1
 */
int token_command(shell_info *datash, char *input)
{
	list_s *head_s, *list_s;
	command_list_s *head_l, *list_l;
	int flag;

	head_s = NULL;
	head_l = NULL;
	_node_add(&head_s, &head_l, input);
	list_s = head_s;
	list_l = head_l;
	while (list_l != NULL)
	{
		datash->command = list_l->command;
		datash->argc = split_line(datash->command);
		flag = _execline(datash);
		free(datash->argc);
		if (flag == 0)
			break;
		go_next(&list_s, &list_l, datash);
		if (list_l != NULL)
			list_l = list_l->next;
	}
	_freeseplist(&head_s);
	_freelinelist(&head_l);
	if (flag == 0)
		return (0);
	return (1);
}
