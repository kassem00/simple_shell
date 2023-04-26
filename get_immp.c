#include "shell.h"
/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
static char *buf;
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;

_putchar(BUF_FLUSH);
r = input_buf(info, &buf, &len);
if (r == -1)
return (-1);
if (len)
{
j = i;
p = buf + i;
check_chain(info, buf, &j, i, len);
while (j < len)
{
if (is_chain(info, buf, &j))
break;
j++;
}
i = j + 1;
if (i >= len)
{
i = len = 0;
info->term_buf_type = L_NORM;
}
*buf_p = p;
return (_strlen(p));
}
*buf_p = buf;
return (r);
}

/**
 * _get__line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: number of bytes read, or -1 on failure
 */
int _get__line(info_t *info, char **ptr, size_t *length)
{
static char buf[BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p)
return (p ? free(p), -1 : -1);
if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}


/**
 * get_environ - returns a copy of the string array containing
 *  our environment variables
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *
 * Return: Pointer to a string array
 */
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}

/**
 * _get__env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value or NULL if not found
 */
char *_get__env(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}

return (NULL);
}


/**
 * get_history_file - gets the path to the history file
 * @info: parameter struct
 *
 * Return: allocated string containing path to history file, or NULL on failure
 */
char *get_history_file(info_t *info)
{
char *buf, *dir;
size_t len;

dir = _get__env(info, "HOME=");
if (!dir)
return (NULL);

len = _strlen(dir) + _strlen(HIST_FILE) + 2;
buf = malloc(sizeof(char) * len);
if (!buf)
return (NULL);

buf[0] = '\0';
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);

return (buf);
}
