#include "main.h"

/**
 * _freelinelist - function to free line in list
 * @head: line_list
 * Return: nothing
 */
void _freelinelist(line_list **head)
{
	line_list *tmp;
	line_list *current;

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
r_var *_addrvar(r_var **head, int var, char *value, int val)
{
	r_var *n, *tmp;

	n = malloc(sizeof(r_var));
	if (n == NULL)
		return (NULL);
	n->len_var = var;
	n->val = value;
	n->len_val = val;
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
 * @head: r_var
 * Return: nothing
 */
void _freervar(r_var **head)
{
	r_var *tmp;
	r_var *current;

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
 * @datash: data_shell
 * Return: int
 */
int _execline(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);
	builtin = get_builtin(datash->args[0]);
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
