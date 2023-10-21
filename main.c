#include "main.h"

/**
 * free_data -
 * @datash:
 * Return:
 */
void free_data(shell_info *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}
	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data -
 * @datash:
 * @av:
 * Return:
 */
void set_data(shell_info *datash, char **argv)
{
	unsigned int i;

	datash->argv = argv;
	datash->command = NULL;
	datash->argc = NULL;
	datash->s = 0;
	datash->c = 1;

	for (i = 0; environ[i]; i++)
		;
	datash->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}
	datash->_environ[i] = NULL;
	datash->pid = _itoa(getpid());
}

/**
 * main -
 * @ac:
 * @av:
 * Return:
 */
int main(int argc, char **argv)
{
	shell_info datash;
	(void) argc;

	signal(SIGINT, get_sigint);
	set_data(&datash, argv);
	_shloop(&datash);
	free_data(&datash);
	if (datash.s < 0)
		return (255);
	return (datash.s);
}

/**
 * get_sigint -
 * @sig:
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
