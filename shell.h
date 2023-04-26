#ifndef _SHELL_H_
#define _SHELL_H_
#define HIST_MAX 4096
#define BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USE_get__LINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}
#define NOT_IMPLEMENTED 98
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
extern char **environ;
/**
 * fun_imp_ - Enumerates a set of functions that can	
 * description: selected based ontheir associated values.
 */
enum fun_imp_
{
HELP, /**< Display help information. */
ENV,  /**< Display environment variables. */
HISTORY,  /**< Display command history. */
SET_ENV,  /**< Set an environment variable. */
UN_SET_ENV,   /**< Unset an environment variable. */
EXIT_T,   /**< Exit the program. */
CAT,  /**< Concatenate files and print on the standard output. */
CMP,  /**< Compare two files. */
CPY,  /**< Copy a file. */
INTRA /**< Perform an intra-network file transfer. */
};

typedef enum fun_imp_ fun_imp_1_t;

/**
 * C_LOGIC_t - Enumerates a set of logical operations
 * that can be selected based on their associated values.
 */
typedef enum C_LOGIC_t
{
L_NORM,   /**< Normal logic operation. */
L_OR, /**< Logical OR operation. */
L_AND,/**< Logical AND operation. */
L_CH  /**< Character comparison operation. */
} C_LOGIC_t;

/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
* struct passinfo - contains pseudo-arguements to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @term_buf: address of pointer to term_buf, on if chaining
* @term_buf_type: term_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
*/
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **term_buf;
int term_buf_type;
int readfd;
int histcount;
} info_t;
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
int  m_fun_1_(info_t *, fun_imp_1_t);
int  _get___fun_imp_type(char *command, info_t *info);
int  m_fun_2_(info_t *info, fun_imp_1_t typ);
char *get_home_dir(info_t *info);
int change_dir(info_t *info, char *path);
void set_old_pwd(info_t *info, char *cwd);
void set_pwd(info_t *info, char *buffer);
void print_cwd(char *cwd);
int _I_impcd(info_t *info);
char *_get__env(info_t *info, const char *name);
int hsh(info_t *, char **);
int _built_finder(info_t *);
void find_term(info_t *);
void fork_term(info_t *);
int is_term(info_t *, char *);
void print_error(info_t *, char *);
int _unsetenv(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int loophsh(char **);
char *_strdup(const char *);
int _putchar(char);
int _eputchar(char);
char **strtow2(char *, char);
char *_strchr(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int is_delim(char, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
int _I_impcd(info_t *);
int _I_impalias(info_t *);
int print_alias(list_t *node);
int replace_alias(info_t *);
int replace_vars(info_t *);
int populate_env_list(info_t *);
int write_history(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char **list_to_strings(list_t *);
char **get_environ(info_t *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _atoi(char *);
void remove_comments(char *);
int _erratoi(char *);
void _eputs(char *);
void _puts(char *);
void sigintHandler(int);
int _isalpha(int);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, const char *);
int _strcmp(char *, char *);
char **strtow(char *, char *);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t read_buf(info_t *info, char *buf, size_t *len);
int set_alias(info_t *info, char *str);
ssize_t get_input(info_t *);
int _get__line(info_t *, char **, size_t *);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_get__env(info_t *, const char *);
char *get_history_file(info_t *info);
int _setenv(info_t *, char *, char *);
int build_history_list(info_t *info, char *buf, int linecount);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);
#endif
