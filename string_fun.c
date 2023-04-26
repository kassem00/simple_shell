#include "shell.h"

/**
* dup_chars - duplicates characters
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to new buffer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
* replace_string - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}

/**
* starts_with - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
* Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}


/**
* check_chain - checks we should continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (info->term_buf_type == L_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->term_buf_type == L_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}