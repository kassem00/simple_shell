#include "shell.h"
/**
 * input_buf - buffers chained commands
 * @info: pointer to struct containing parameters
 * @buf: address of buffer
 * @len: address of len variable
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
if (!*len)
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_get__LINE
r = getline(buf, &len_p, stdin);
#else
r = _get__line(info, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0';
r--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
{
*len = r;
info->term_buf = buf;
}
}
}
return (r);
}

/**
 * read_buf - reads a buffer from a file descriptor
 * @info: parameter struct
 * @buf: buffer to store read data
 * @i: pointer to size variable
 * Return: number of bytes read
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;
if (*i)
return (0);

r = read(info->readfd, buf, BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}
/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
