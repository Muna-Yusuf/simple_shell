#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>



extern char **environ;
#define DELIMITER " \t\n"
#define BUFSIZE 1024
#define BUFSIZE_X 128

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
char *_strtok(char commands[], const char *delim);
int check_digit(const char *s);
void _strrev(char *s);
char *_itoa(int n);
int _atoi(char *s);
int _numlen(int num);
char *swapping(char *input, int bool);
void _node_add(sep_list **head_s, line_list **head_l, char *input);/*mnmnm*/

void _node_next(sep_list **list_s, line_list **list_l, data_shell *datash); /***/
int token_command(data_shell *datash, char *input); /***/
char **tokenization(char *command)
int (*get_builtin(char *cmd))(data_shell *);/***/
int _cdir(char *path, int *x);
char *_wh(char *cmd, char **_environ);
void cd_command(shell_info *infosh);
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
char *envir_error(shell_info *infosh);
char *error_126(shell_info *infosh);
void _enviro_check(command_var_r **dot, char *i, shell_info *infosh);
void _enviro_check(command_var_r **dot, char *i, shell_info *infosh);
int _vars_ch(command_var_r **dot, char *x, char *str, shell_info *infosh);
char *_replaced(command_var_r **dot, char *input, char *input2, int length);
int _exec(data_shell *datash);/**/
int _errcheck(char *d, data_shell *datash);/**/
int _execute(data_shell *datash);/**/
int _exit(shell_info *infosh);
char *_readline(int *x);
void _bringline(char **ptr, size_t *n, char *b, size_t k);
ssize_t _getline(char **ptr, size_t *n, FILE *s);
void _freelinelist(line_list **head);/**/
/**
 * struct info - strcut.
 * @argv:
 */
typedef struct info /* data */
{
	char **argv; /*av*/
	char **argc; /*args*/
	char *command;/*intput*/
	int s;
	int c;
	char **_environ;
	char *pid;
} shell_info; /* data_shell  */

/**
 *
 *
 *
 */
typedef struct list /* sep_list_s */
{
	char sep;
	struct list *next;
} list_s; /*sep_list*/

/**
 *
 *
 *
 */
typedef struct command_list /*  line_list_s */
{
	char *command;
	struct command_list *next;
} command_list_s; /* line_list*/

/**
 *
 *
 *
 */
typedef struct command_var /* r_var_list  */
{
	int length; /*len_bar*/
	char *value;/*val*/
	int length_value;/*len_val*/
	struct command_var *next;
} command_var_r; /* r_var */

typedef struct builtin_exe /*builtin_s*/
{
	char *command;/*name*/
	int (*b)(shell_info *infosh); /* data_shell *datash */
} builtin_exe_x; /* builin_t/
