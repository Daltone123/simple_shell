
#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @number: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int number;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @paths: a string path for the current command
 * @argc: the argument count
 * @forlinecount: the error count
 * @err_number: the error code for exit()s
 * @linecount_flags: if on count this line of input
 * @f_names: the program filename
 * @envv: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @my_history: the history node
 * @alias: the alias node
 * @envv_change: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buf, on if chaining
 * @cmdbuftype: CMD_type ||, &&, ;
 * @to_readfd: the fd from which to read line input
 * @forhistcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *paths;
	int argc;
	unsigned int forlinecount;
	int err_number;
	int linecount_flags;
	char *f_names;
	list_t *envv;
	list_t *my_history;
	list_t *alias;
	char **environ;
	int envv_change;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdbuftype; /* CMD_type ||, &&, ; */
	int to_readfd;
	int forhistcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int for_finding_builtin(info_t *);
void for_finding_cmd(info_t *);
void for_fork_cmd(info_t *);


int is_cmd(info_t *, char *);
char *for_dup_chars(char *, int, int);
char *for_finding_path(info_t *, char *, char *);


int loophsh(char **);

void for_eputs(char *);
int for_eputchar(char);
int for_putfd(char c, int fdd);
int for_putsfd(char *str, int fdd);

int for_strlength(char *);
int for_strcmp(char *, char *);
char *for_starting_with(const char *, const char *);
char *for_strcat(char *, char *);

char *for_strcpy(char *, char *);
char *for_strdup(const char *);
void for_puts(char *);
int for_putchar(char);

char *for_strncpy(char *, char *, int);
char *for_strncat(char *, char *, int);
char *for_strchr(char *, char);

char **to_strtow(char *, char *);
char **to_strtow2(char *, char);

char *for_memset(char *, char, unsigned int);
void for_free(char **);
void *to_realloc(void *, unsigned int, unsigned int);

int be_free(void **);

int for_interact(info_t *);
int deliminator(char, char *);
int alphabetic(int);
int for_atoi(char *);

int for_erratoi(char *);
void for_printing_error(info_t *, char *);
int for_printing_d(int, int);
char *for_converting_number(long int, int, int);
void for_removing_comments(char *);

int for_myexit(info_t *);
int for_mycd(info_t *);
int for_myhelp(info_t *);

int for_myhistory(info_t *);
int for_myalias(info_t *);

ssize_t for_get_input(info_t *);
int for_getline(info_t *, char **, size_t *);
void for_sigintHandler(int);

void for_clearing_info(info_t *);
void for_setting_info(info_t *, char **);
void for_free_info(info_t *, int);

char *for_getenvv(info_t *, const char *);
int for_myenvv(info_t *);
int for_mysetenvv(info_t *);
int for_myunsetenvv(info_t *);
int for_populate_envv_list(info_t *);

char **for_get_environs(info_t *);
int for_unsetenvv(info_t *, char *);
int for_setenvv(info_t *, char *, char *);

char *for_history_file(info_t *infom);
int for_write_history(info_t *infom);
int for_read_history(info_t *infom);
int to_build_history_list(info_t *infom, char *buffer, int forlinecount);
int to_renumber_history(info_t *infom);

list_t *to_add_node(list_t **, const char *, int);
list_t *for_add_node_end(list_t **, const char *, int);
size_t for_printing_list_str(const list_t *);
int for_delete_node_at_index(list_t **, unsigned int);
void to_free_list(list_t **);

size_t list_legth(const list_t *);
char **for_list_to_strings(list_t *);
size_t for_printing_list(const list_t *);
list_t *for_node_starts_with(list_t *, char *, char);
ssize_t for_get_node_index(list_t *, list_t *);

int for_chain(info_t *, char *, size_t *);
void to_check_chain(info_t *, char *, size_t *, size_t, size_t);
int for_replacing_alias(info_t *);
int for_replacing_vars(info_t *);
int for_replacing_string(char **, char *);

#endif


