#include "shell.h"


void _eputs(char *str)
{
int i = 0;

if (!str)
return;

while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}


void print_error(info_t *info, char *estr)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(estr);
}


int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;

if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;

current = _abs_;

for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}

current %= i;
}

__putchar('0' + current);
count++;

return (count);
}


size_t print_list(const list_t *h)
{
size_t i = 0;

while (h)
{
_puts(convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}

return (i);
}
