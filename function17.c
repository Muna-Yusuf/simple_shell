#include "main.h"

/**
 * go_next - function.
 * @listx: struct.
 * @list_l: strcut.
 * @datash: strcut.
 * Return: void
 */
void go_next(list_s **listx, command_list_s **list_l, shell_info *datash)
{
	int loop_sep;
	list_s *ls_s;
	command_list_s *ls_l;

	loop_sep = 1;
	ls_s = *listx;
	ls_l = *list_l;
	while (ls_s != NULL && loop_sep)
	{
		if (datash->s == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}
	*listx = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - function.
 * @infosh: sturct.
 * @command: char.
 * Return: int.
 */
int split_commands(shell_info *infosh, char *command)
{
	list_s *head_s, *list_s;
	command_list_s *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;
	_node_add(&head_s, &head_l, command);
	list_s = head_s;
	list_l = head_l;
	while (list_l != NULL)
	{
		infosh->command = list_l->command;
		infosh->argc = split_line(infosh->command);
		loop = _execline(infosh);
		free(infosh->argc);
		if (loop == 0)
			break;
		go_next(&list_s, &list_l, infosh);
		if (list_l != NULL)
			list_l = list_l->next;
	}
	_freeseplist(&head_s);
	_freelinelist(&head_l);
	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - function to tokenize
 * @input: char
 * Return: char
*/
char **split_line(char *input)
{
	size_t size;
	size_t m;
	char **tokens;
	char *token;

	size = BUFSIZE_X;
	tokens = malloc(sizeof(char *) * (size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, DELIMITER);
	tokens[0] = token;
	for (m = 1; token != NULL; m++)
	{
		if (m == size)
		{
			size += BUFSIZE_X;
			tokens = _reallocdup(tokens, m, sizeof(char *) * size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, DELIMITER);
		tokens[m] = token;
	}
	return (tokens);
}
