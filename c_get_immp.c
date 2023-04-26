#include "shell.h"

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



char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}


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
