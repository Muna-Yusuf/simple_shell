#include "main.h"

/**
 * _freelinelist - function to free line in list
 * @head: line_list
 * Return: nothing
 */
void _freelinelist(command_list_s **head)
{
	command_list_s *tmp;
	command_list_s *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * _addrvar - function to add var node
 * @head: r_var
 * @var: var length
 * @value: char
 * @val: value length
 * Return: r_var
 */
command_var_r *_addrvar(command_var_r **head, int var, char *value, int val)
{
	command_var_r *n, *tmp;

	n = malloc(sizeof(command_var_r));
	if (n == NULL)
		return (NULL);
	n->length_value = var;
	n->value = value; /* this */
	n->length_value = val;
	n->next = NULL;
	tmp = *head;
	if (tmp == NULL)
		*head = n;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = n;
	}
	return (*head);
}

/**
 * _freervar - function to free r_var
 * @head: struct
 * Return: nothing
 */
void _freervar(command_var_r **head)
{
	command_var_r *tmp;
	command_var_r *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * exec_line - function to execute line
 * @datash: strcut.
 * Return: int
 */
int _execline(shell_info *datash)
{
	int (*builtin)(shell_info *datash);

	if (datash->argc[0] == NULL)
		return (1);
	builtin = get_builtin(datash->argc[0]);
	if (builtin != NULL)
		return (builtin(datash));
	return (cmd_exec(datash));
}

/**
 * _memcopy - functopn to copy
 * @nptr: new pointer
 * @ptr: pointer
 * @size: size
 * Return: nothing
 */
void _memcopy(void *nptr, const void *ptr, unsigned int size)
{
	char *optr = (char *)ptr;
	char *newptr = (char *)nptr;
	unsigned int m;

	for (m = 0; m < size; m++)
		newptr[m] = optr[m];
}
