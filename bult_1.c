#include "shell.h"
/**
* m_fun_1_ - fuction cluster togther.
* @info: arguments container.
* @typ: what funcation will be used.
* Return: int value
*/
int m_fun_1_(info_t *info, fun_imp_1_t typ)
{
int i;
switch (typ)
{
case ENV:
print_list_str(info->env);
return (0);
break;
case SET_ENV:
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
break;
case UN_SET_ENV:
if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
_unsetenv(info, info->argv[i]);
return (0);
break;
case HISTORY:
print_list(info->history);
return (0);
break;
case INTRA:
return (isatty(STDIN_FILENO) && info->readfd <= 2);
break;
default:
break;
}
return (NOT_IMPLEMENTED);
}



/**
* m_fun_2_ - fuction cluster togther.
* @info: arguments container.
* @typ: what funcation will be used.
* Return: int value
*/
int m_fun_2_(info_t *info, fun_imp_1_t typ)
{
char **arg_array;
int exitcheck;
switch (typ)
{
case HELP:
arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
break;
case EXIT_T:
if (info->argv[1]) /* If there is an exit arguement */
{
exitcheck = _erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = _erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
break;
default:
break;
}
return (NOT_IMPLEMENTED);
}
/**
* _get___fun_imp_type - exits the shell
* @info: arguments container.
* @command: arguments to pass for function.
* Return: int value
*/
int _get___fun_imp_type(char *command, info_t *info)
{
if (_strcmp(command, "env") == 0)
{
return (m_fun_1_(info, ENV));
}
else if (_strcmp(command, "history") == 0)
{
return (m_fun_1_(info, HISTORY));
}
else if (_strcmp(command, "setenv") == 0)
{
return (m_fun_1_(info, SET_ENV));
}
else if (_strcmp(command, "unsetenv") == 0)
{
return (m_fun_1_(info, UN_SET_ENV));
}
else if (_strcmp(command, "exit") == 0)
{
return (m_fun_2_(info, EXIT_T));
}
else if (_strcmp(command, "help") == 0)
{
return (m_fun_2_(info, HELP));
}
else
{
return (NOT_IMPLEMENTED);
}
}
/**
* _built_finder - finds a builtin command
* @info: the parameter & return info struct
* Return: int value
*/
int _built_finder(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit",  NULL},
{"env", NULL},
{"help",  NULL},
{"history", NULL},
{"setenv", NULL},
{"unsetenv", NULL},
{"cd", _I_impcd},
{"alias", _I_impalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
if (_strcmp(info->argv[0], "history") == 0 ||
_strcmp(info->argv[0], "env") == 0 ||
_strcmp(info->argv[0], "setenv") == 0 ||
_strcmp(info->argv[0], "exit") == 0 ||
_strcmp(info->argv[0], "help") == 0 ||
_strcmp(info->argv[0], "unsetenv") == 0)
{
info->line_count++;
built_in_ret =  _get___fun_imp_type(info->argv[0], info);
}
else
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
}
return (built_in_ret);
}
