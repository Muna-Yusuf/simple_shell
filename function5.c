#include "main.h"

/**
 * tokenization - function to tokenize the command
 * @command: char
 * Return: char
 */
char **tokenization(char *command)
{
	size_t size;
	size_t m;
	char **tokens;
	char *tok;

	size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	tok = _strtok(command, TOK_DELIM);
	tokens[0] = tok;
	for (m = 1; tok != NULL; m++)
	{
		if (m == size)
		{
			size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, m, sizeof(char *) * size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = _strtok(NULL, TOK_DELIM);
		tokens[m] = tok;
	}
	return (tokens);
}

/**
 * get_builtin - function to get the command
 * @cmd: char
 * Return: command execution
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int m;

	for (m = 0; builtin[m].name; m++)
	{
		if (_strcmp(builtin[m].name, cmd) == 0)
			break;
	}
	return (builtin[m].f);
}

/**
 * com_get - function
 * @s: integer
 * Return: nothing
 */
void com_get(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * is_cdir - function
 * @path: character
 * @x: integer
 * Return: 0 or 1
 */
int _cdir(char *path, int *x) /*not written in main??????????*/
{
	if (path[*x] == ':')
		return (1);
	while (path[*x] != ':' && path[*x])
	{
		*x += 1;
	}
	if (path[*x])
		*x += 1;
	return (0);
}

/**
 * _wh - function
 * @cmd: char
 * @_environ: char
 * Return: char
 */
char *_wh(char *cmd, char **_environ)
{
	char *path, *ptr, *token, *dir;
	int len_dir, len_cmd, m;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr = _strdup(path);
		len_cmd = _strlen(cmd);
		token = _strtok(ptr, ":");
		m = 0;
		while (token != NULL)
		{
			if (is_cdir(path, &m))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr);
				return (dir);
			}
			free(dir);
			token = _strtok(NULL, ":");
		}
		free(ptr);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
