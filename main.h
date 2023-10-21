#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>


extern char **environ;
#define DELIMITER " \t\n"
#define BUFSIZE 1024
#define BUFSIZE_X 128

/**
 * struct info - strcut.
 * @argv: char.
 * @argc: char.
 * @s: int.
 * @c: int.
 * @_environ: char.
 * @pid: char.
 */
typedef struct info
{
	char **argv;
	char **argc;
	char *command;
	int s;
	int c;
	char **_environ;
	char *pid;
} shell_info;

/**
 * struct list - struct.
 * @sep: char.
 * @next: struct.
 */
typedef struct list
{
	char sep;
	struct list *next;
} list_s;

/**
 * struct command_list - strcut.
 * @command: char
 * @next: struct.
 */
typedef struct command_list
{
	char *command;
	struct command_list *next;
} command_list_s;

/**
 * struct command_var - struct.
 * @length: int.
 * @value: char
 * @length_value: int.
 * @next: strcut.
 */
typedef struct command_var
{
	int length;
	char *value;
	int length_value;
	struct command_var *next;
} command_var_r;
/**
 * struct builtin_exe - struct.
 * @command: char.
 * @b: steuct.
 */
typedef struct builtin_exe
{
	char *command;
	int (*b)(shell_info *infosh);
} builtin_exe_x;

char *re_v(char *input, shell_info *infosh);
void get_sigint(int sig);
ssize_t _getline(char **ptr, size_t *n, FILE *s);
void _freelinelist(command_list_s **head);
char *error_exit_shell(shell_info *datash);
char *error_not_found(shell_info *datash);
void _shloop(shell_info *datash);
void free_data(shell_info *datash);
void set_data(shell_info *datash, char **argv);
list_s *_sepend(list_s **head, char s);
void _freeseplist(list_s **head);
command_list_s *_lineend(command_list_s **head, char *l);
command_var_r *_addrvar(command_var_r **head, int var, char *value, int val);
void _freervar(command_var_r **head);
int _execline(shell_info *datash);
void _memcpy(void *nptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int size, unsigned int newsize);
char **_reallocdup(char **ptr, unsigned int size, unsigned int newsize);
void _help(void);
void _helpalias(void);
void _helpcd(void);
void _helpenv(void);
void _helpsetenv(void);
void _helpunsetenv(void);
void _helpgeneral(void);
void _helpexit(void);
char *_nocomment(char *in);
char *error_not_found(shell_info *datash);
char *error_exit_shell(shell_info *datash);
int _cdir(char *path, int *x);
char *_wh(char *cmd, char **_environ);
void cd_command(shell_info *infosh);
int _vars_ch(command_var_r **dot, char *x, char *str, shell_info *infosh);
void cd_command2(shell_info *infosh);
void cd_command_perv(shell_info infosh);
void cd_command_home(shell_info infosh);
int shell_command(shell_info *infosh);
int char_rep(char *command, int x);
int sep_err(char *command, int x, char com_l);
int char_f(char *command, int *x);
void error_print(shell_info *infosh, char *command, int x, int bool);
int error_ck(shell_info *infosh, char *command);
int env_comp(const char *xenv, const char *name);
char *_getenv(const char *commands, char **_environ);
int _env(shell_info *infosh);
char *info(char *name, char *value);
void set_env(char *command, char *value, shell_info *infosh);
int _setenv(shell_info *infosh);
int _unsetenv(shell_info *infosh);
int get_error(shell_info *infosh, int l);
char *_cd_str(shell_info *infosh, char *m, char *error_co, char *value);
char *error_cd(shell_info *infosh);
char *envir_error(shell_info *infosh);
char *error_126(shell_info *infosh);
void _enviro_check(command_var_r **dot, char *i, shell_info *infosh);
int _vars_ch(command_var_r **dot, char *x, char *str, shell_info *infosh);
char *_replaced(command_var_r **dot, char *input, char *input2, int length);
int _exec(shell_info *datash);
int _errcheck(char *d, shell_info *datash);
int _execute(shell_info *datash);
int _exitx(shell_info *infosh);
char *_readline(int *x);
void _bringline(char **ptr, size_t *n, char *b, size_t k);
int _strcmp(char *str1, char *str2);
int _putchar(char *c);
char *_strcpy(char *dest, char *src);
int _strlen(const char *s);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
char *_strtok(char commands[], const char *delim);
int check_digit(const char *s);
void _strrev(char *s);
char *_itoa(int n);
int _atoi(char *s);
int _numlen(int num);
char *swapping(char *input, int bool);
void _node_add(list_s **head_s, command_list_s **head_l, char *command);
void _node_next(list_s **lists, command_list_s **listl, shell_info *infosh);
int token_command(shell_info *datash, char *input);
char **tokenization(char *command);
int (*get_builtin(char *cmd))(shell_info *);
char *_strcat(char *dest, char *src);
void _free(shell_info *infosh);

#endif
