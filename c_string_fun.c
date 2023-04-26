#include "shell.h"


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


int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}


char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}



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
