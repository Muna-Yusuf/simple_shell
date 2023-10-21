#include "main.h"

/**
 * _bringline - function to bring line
 * @ptr: char
 * @b: char
 * @n: of type size_t
 * @k: of type size_t
 * Return: nothing
 */
void _bringline(char **ptr, size_t *n, char *b, size_t k)
{

	if (*ptr == NULL)
	{
		if  (k > BUFSIZE)
			*n = k;
		else
			*n = BUFSIZE;
		*ptr = b;
	}
	else if (*n < k)
	{
		if (k > BUFSIZE)
			*n = k;
		else
			*n = BUFSIZE;
		*ptr = b;
	}
	else
	{
		_strcpy(*ptr, b);
		free(b);
	}
}
/**
 * _getline - function to get line
 * @ptr: char
 * @n: size_t
 * @s: FILE
 * Return: returned value
 */
ssize_t _getline(char **ptr, size_t *n, FILE *s)
{
	int m;
	static ssize_t in;
	ssize_t val;
	char *b;
	char t = 'z';

	if (in == 0)
		fflush(s);
	else
		return (-1);
	in = 0;
	b = malloc(sizeof(char) * BUFSIZE);
	if (b == 0)
		return (-1);
	while (t != '\n')
	{
		m = read(STDIN_FILENO, &t, 1);
		if (m == -1 || (m == 0 && in == 0))
		{
			free(b);
			return (-1);
		}
		if (m == 0 && in != 0)
		{
			in++;
			break;
		}
		if (in >= BUFSIZE)
			b = _realloc(b, in, in + 1);
		b[in] = t;
		in++;
	}
	b[in] = '\0';
	_bringline(ptr, n, b, in);
	val = in;
	if (m != 0)
		in = 0;
	return (val);
}

/**
 * _sepend - function to add separator at the end node
 * @head: sep_list
 * @s: separator (; | &)
 * Return: sep_list
 */
list_s *_sepend(list_s **head, char s)
{
	list_s *n, *tmp;

	n = malloc(sizeof(list_s));
	if (n == NULL)
		return (NULL);
	n->sep = s;
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
 * _freeseplist - function to free separator list
 * @head: sep_list
 * Return: nothing
 */
void _freeseplist(list_s **head)
{
	list_s *tmp;
	list_s *current;

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
 * _lineend - function to add line at the end node
 * @head: line_list
 * @l: char
 * Return: line_list
 */
command_list_s *_lineend(command_list_s **head, char *l)
{
	command_list_s *n, *tmp;

	n = malloc(sizeof(command_list_s));
	if (n == NULL)
		return (NULL);
	n->command = l;
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
