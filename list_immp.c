#include "shell.h"

/**
 * list_len - Determines the length of linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}

return (i);
}

/**
 * list_to_strings - Returns an array of strings of the list->str.
 * @head: Pointer to first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);

strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);

for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;

return (strs);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t print_list_str(const list_t *h)
{
size_t i = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}

return (i);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to head node.
 *
 * Return: Void.
 */
void free_list(list_t **head_ptr)
{
list_t *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;

head = *head_ptr;
node = head;

while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}

*head_ptr = NULL;
}
