#include "main.h"

/**
 * cd_command - function that exe cd.
 * @infosh: struct.
 * Return: void.
 */
void cd_command(shell_info *infosh)
{
	char command_pwd[PATH_MAX];
	char *dirct, *_pwd, *_pwd_cp;

	getcwd(command_pwd, sizeof(commmand_pwd));/*function)*/
	_pwd = _strdup(command_pwd);
	set_env("OLDPWD", _pwd, infosh);
	dirct = infosh->argc[1]; /*argc*/
	if (_strcmp(".", dirct) == 0)
	{
		set_env("PWD", _pwd, infosh);
		free(_pwd);
		return;
	}
	if (_strcmp("/", _pwd) == 0)
	{
		free(_pwd);
		return;
	}
	_pwd_cp = _pwd;
	_strrev(_pwd_cp);
	_pwd_cp = _strtok(_pwd_cp, "/");
	if (_pwd_cp != NULL)
	{
		_pwd_cp = _strtok(NULL, "\0");
		if (_pwd_cp != NULL)
		{
			_strrev(_pwd_cp);
		}
	}
	if (_pwd_cp != NULL)
	{
		chdir(_pwd_cp);
		set_env("PWD", _pwd_cp, infosh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", infosh);
	}
	infosh->s = 0;
	free(_pwd);
}

/**
 * cd_command2 - function that cd.
 * @infosh: struct.
 * Return: void.
 */

void cd_command2(shell_info *infosh)
{
	char command_pwd[PATH_MAX];
	char *dirct, *_pwd, *_pwd_cp;

	getcwd(command_pwd, sizeof(command_pwd)); /* function */

	dirct = infosh->argc[1]; /* args */
	if (chdir(dirct) == -1)
	{
		get_error(infosh, 2);
		return;
	}
	_pwd = _strdup(command_pwd);
	set_env("OLDPWD", _pwd, infosh);

	_pwd_cp = _strdup(dirct);
	set_env("OLDPWD", _pwd_cp, infosh);
	free(_pwd);
	free(_pwd_cp);
	infosh->s = 0;
	chdir(dirct);
}

/**
 * cd_command_perv - function that cd previous.
 * @infosh: struct.
 * Return: void.
 */
void cd_command_perv(shell_info infosh)
{
	char command_pwd[PATH_MAX];
	char *_pwd_p, *_pwd_o, *_pwd_cp, *_pw_ocp;

	getcwd(command_pwd, sizeof(command_pwd)); /* function */
	_pwd_cp = _strdup(command_pwd);

	_pwd_o = _getenv("OLDPWD", infosh->_environ);
	if (_pwd_o == NULL)
	{
		_pw_ocp = _pwd_cp;
	}
	else
	{
		_pw_ocp = _strdup(_pwd_o)
	}

	set_env("OLDPWD", _pwd_cp, infosh);

	if (chdir(_pw_ocp) == -1)
	{
		set_env("PWD", _pwd_cp, infosh);
	}
	else
	{
		set_env("PWD", _pwd_ocp, infosh);
	}

	_pwd_p = _getenv("PWD", infosh->_environ);

	_putchar(_pwd_p);
	_putchar("/n");

	free(_pwd_cp);
	if (_pwd_o)
	{
		free(_pw_ocp);
	}
	infosh->s = 0;
	chdir(_pwd_p);
}

/**
 * cd_command_home - function that to home.
 * @infosh: struct.
 * Return: void.
 */

void cd_command_home(shell_info infosh)
{
	char pwd_command[PATH_MAX];
	char *_pwd_p, *p_home;

	getcwd(pwd_command, sizeof(pwd_command)); /* function */
	_pwd_p = strdup(pwd_command);

	p_home = _getenv("HOME", infosh->_environ);

	if (p_home == NULL)
	{
		set_env("OLDPWD", _pwd_p, infosh);
		free(_pwd_p);
		return;
	}
	if (chdir(p_home) == -1)
	{
		get_error(infosh, 2);
		free(_pwd_p);
		return;
	}
	set_env("OLDPWD", _pwd_p, infosh);
	set_env("PWD", p_home, infosh);
	free(_pwd_p);
	infosh->s = 0;

}

/**
 * shell_command - function that exe.
 * @infosh: struct.
 * Return: int.
 */

int shell_command(shell_info *infosh)
{
	char *dirct;
	int x, y, z;

	dirct = infosh->argc[1];

	if (dirct != NULL)
	{
		x = _strcmp("$HOME", dirct);
		y = _strcmp("~", dirct);
		z = _strcmp("--", dirct);
	}
	if (dirct == NULL || !x || !y || !z)
	{
		cd_command_home(infosh);
		return (1);
	}
	if (_strcmp("-", dirct) == 0)
	{
		cd_command_perv(infosh);
		return (1);
	}
	if (_strcmp(".", dirct) == 0 || _strcmp("..", dirct) == 0)
	{
		cd_command(infosh);
		return (1);
	}
	cd_command2(infosh);
	return (1);
}
