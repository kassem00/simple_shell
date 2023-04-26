#include "shell.h"
/**
 * _strcat - Concatenates two strings.
 *
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;

    return (ret);
}
/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: difference between the first non-matching characters
 *         of @s1 and @s2, 0 if strings are identical
 */
int _strcmp(char *s1, char *s2)
{
        while (*s1 && *s2)
        {
                if (*s1 != *s2)
                        return (*s1 - *s2);
                s1++;
                s2++;
        }
        return (*s1 - *s2);
}

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, const char *src)
{
        int i;

        if (dest == src || src == 0)
                return (dest);

        for (i = 0; src[i]; i++)
                dest[i] = src[i];

        dest[i] = '\0';

        return (dest);
}
/**
 * strtow - Splits a string into words using a delimiter
 * @str: String to be split
 * @delim: Delimiter used to split the string
 *
 * Return: Pointer to an array of strings or NULL on failure
 */
char **strtow(char *str, char *delim)
{
        int i, j, k, m, num_words = 0;
        char **words;

        if (str == NULL || str[0] == '\0')
                return (NULL);

        if (delim == NULL)
                delim = " ";

        for (i = 0; str[i] != '\0'; i++)
                if (!is_delim(str[i], delim) &&
                    (is_delim(str[i + 1], delim) || str[i + 1] == '\0'))
                        num_words++;

        if (num_words == 0)
                return (NULL);

        words = malloc((num_words + 1) * sizeof(char *));
        if (words == NULL)
                return (NULL);

        for (i = 0, j = 0; j < num_words; j++)
        {
                while (is_delim(str[i], delim))
                        i++;

                k = 0;
                while (!is_delim(str[i + k], delim) && str[i + k] != '\0')
                        k++;

                words[j] = malloc((k + 1) * sizeof(char));
                if (words[j] == NULL)
                {
                        for (k = 0; k < j; k++)
                                free(words[k]);
                        free(words);
                        return (NULL);
                }

                for (m = 0; m < k; m++)
                        words[j][m] = str[i++];

                words[j][m] = '\0';
        }

        words[j] = NULL;

        return (words);
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == '\0')
        return (NULL);

    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != d && str[i + 1] == d) ||
            (str[i] != d && !str[i + 1]) || str[i + 1] == d)
            numwords++;
    }

    if (numwords == 0)
        return (NULL);

    s = malloc((numwords + 1) * sizeof(char *));
    if (s == NULL)
        return (NULL);

    for (i = 0, j = 0; j < numwords; j++)
    {
        while (str[i] == d && str[i] != d)
            i++;

        k = 0;
        while (str[i + k] != d && str[i + k] != '\0')
            k++;

        s[j] = malloc((k + 1) * sizeof(char));
        if (s[j] == NULL)
        {
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }

        for (m = 0; m < k; m++)
            s[j][m] = str[i++];

        s[j][m] = '\0';
    }

    s[j] = NULL;
    return (s);
}
