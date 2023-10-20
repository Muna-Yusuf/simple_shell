#include "main.h"

/**
 * _helpenv - function
 * Return: nothing
 */
void _helpenv(void)
{
	char *x = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, x, _strlen(x));
	x = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, x, _strlen(x));

}
/**
 * _helpsetenv - function
 * Return: nothing
 */
void _helpsetenv(void)
{

	char *x = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, x, _strlen(x));
	x = "int replace)\n\t";
	write(STDOUT_FILENO, x, _strlen(x));
	x = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, x, _strlen(x));
}

/**
 * _helpunsetenv - function
 * Return: nothing
 */
void _helpunsetenv(void)
{
	char *x = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, x, _strlen(x));
	x = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, x, _strlen(x));
}

/**
 * _helpgeneral - function
 * Return: nothing
 */
void _helpgeneral(void)
{
	_putchar("^-^ bash, version 1.0(1)-release\n");
	_putchar("These commands are defined internally.Type 'help' to see the list");
	_putchar("Type 'help name' to find out more about the function 'name'.\n\n ");
	_putchar(" alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ");
	_putchar("[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ");
	_putchar("[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ");
	_putchar("unsetenv [variable]\n");
}

/**
 * _helpexit - function
 * Return: nothing
 */
void _helpexit(void)
{
	_putchar("exit: exit [n]\n Exit shell.\n");
	_putchar("Exits the shell with a status of N. If N is ommited, the exit");
	_putchar("statusis that of the last command executed\n");
}
