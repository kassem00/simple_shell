#include "shell.h"
/**
 * find_term - Finds a command in PATH.
 * @info: Pointer to the info struct.
 *
 * Return: void.
 */
void find_term(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];

if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}

for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;

if (!k)
return;

path = find_path(info, _get__env(info, "PATH="), info->argv[0]);

if (path)
{
info->path = path;
fork_term(info);
}
else
{
if ((m_fun_1_(info, INTRA) || _get__env(info, "PATH=") ||
info->argv[0][0] == '/') && is_term(info, info->argv[0]))
fork_term(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}
/**
 * find_path - finds the full path of a term in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @term: the term to find
 *
 * Return: full path of term if found, NULL otherwise
 */
char *find_path(info_t *info, char *pathstr, char *term)
{
int i = 0, curr_pos = 0;
char *path = NULL;

if (!pathstr)
return (NULL);

if ((_strlen(term) > 2) && starts_with(term, "./"))
{
if (is_term(info, term))
return (term);
}

while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);

if (!*path)
_strcat(path, term);
else
{
_strcat(path, "/");
_strcat(path, term);
}

if (is_term(info, path))
return (path);

if (!pathstr[i])
break;

curr_pos = i;
}
i++;
}

return (NULL);
}

/**
 * remove_comments - replace first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: void
 */
void remove_comments(char *buf)
{
int i;
for (i = 0; buf[i] != '\0'; i++)
{
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
}
