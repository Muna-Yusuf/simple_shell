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
 * @input: char
 * Return: nothing
 */
void _node_add(sep_list **head_s, line_list **head_l, char *input)
{
	int m;
	char *l;

	input = swap_char(input, 0);
	for (m = 0; input[m]; m++)
	{
		if (input[m] == ';')
			add_sep_node_end(head_s, input[m]);
		if (input[m] == '|' || input[m] == '&')
		{
			add_sep_node_end(head_s, input[m]);
			m++;
		}
	}
	l = _strtok(input, ";|&");
	do {
		l = swap_char(l, 1);
		add_line_node_end(head_l, l);
		l = _strtok(NULL, ";|&");
	} while (l != NULL);

}

/**
 * _node_next - function to go to the next node
 * @list_s: of type sep_list
 * @list_l: of type line_list
 * @datash: of type data_shell
 * Return: nothing
 */
void _node_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int m;
	sep_list *s;
	line_list *l;

	m = 1;
	s = *list_s;
	l = *list_l;
	while (s != NULL && m)
	{
		if (datash->status == 0)
		{
			if (s->separator == '&' || s->separator == ';')
				m = 0;
			if (s->separator == '|')
				l = l->next, s = s->next;
		}
		else
		{
			if (s->separator == '|' || s->separator == ';')
				m = 0;
			if (s->separator == '&')
				l = l->next, s = s->next;
		}
		if (s != NULL && !m)
			s = s->next;
	}
	*list_s = s;
	*list_l = l;
}

/**
 * token_command - function to tokenize commands
 * @datash: of type data_shell
 * @input: char
 * Return: 0 or 1
 */
int token_command(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int flag;

	head_s = NULL;
	head_l = NULL;
	add_nodes(&head_s, &head_l, input);
	list_s = head_s;
	list_l = head_l;
	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		flag = exec_line(datash);
		free(datash->args);
		if (flag == 0)
			break;
		go_next(&list_s, &list_l, datash);
		if (list_l != NULL)
			list_l = list_l->next;
	}
	free_sep_list(&head_s);
	free_line_list(&head_l);
	if (flag == 0)
		return (0);
	return (1);
}
