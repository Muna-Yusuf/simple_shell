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

int _putchar(char *c);
int _strlen(const char *s);
char *_strdup(const char *str);
int _str_free(char **str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);


char *_strchr(char *s, char c); /* this is ?*/
int _strspn(char *s, char *accept); /* this is */
int char_comp(char str[]); /*DELIMITER */
int check_digit(const char *s) /* int _isdigit(const char *s) */
void _strrev(char *str);


int _numlen(int num);
int _atoi(char *s);
char *_itoa(int n);
char *swapping(char *input, int bool);
void _node_add(sep_list **head_s, line_list **head_l, char *input);
void _node_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int token_command(data_shell *datash, char *input); /* int split_commands */
char **tokenization(char *command) /* char **split_line(char *input)  */
int (*get_builtin(char *cmd))(data_shell *); /* exe_fun  */


char *_strtok(char commands[]); /* DELIMITER */
void _free(shell_info *infosh);/* ?????? */
void com_get(int s); /* void get_sigint(int sig) */

/*		env      	*/
void env_command(const char *xenv, const char *name);
char *_getenv(const char *commands) /* char **_environ  */
int int_env_command(data_shell *datash);
char *info(char *name, char *value);
void cd_command();

/*		structs 	*/

typedef struct info
{
	char **argv;
	char **argc;
	char command;
	int s ;
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
} list_s;

/**
 *
 *
 *
 */
typedef struct command_list /*  line_list_s */
{
	char *command;
	struct command_list *next;
} command_list_s;

/**
 *
 *
 *
 */
typedef struct command_var /* r_var_list  */
{
	int length;
	char value;
	int length_value;
	struct command_var *next;
} command_var_r;

typedef struct builtin_exe
{
	char *command;
	int (b)(shell_info *infosh); /* data_shell *datash */
} builtin_exe_x;
