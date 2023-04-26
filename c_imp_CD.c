#include "shell.h"


char *get_home_dir(info_t *info)
{
char *dir = _get__env(info, "HOME=");
if (!dir)
dir = _get__env(info, "PWD=");
return (dir);
}


int change_dir(info_t *info, char *path)
{
int chdir_ret = chdir(path);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(path), _eputchar('\n');
}
return (chdir_ret);
}


void print_cwd(char *cwd)
{
_puts(cwd), _putchar('\n');
}


int _I_impcd(info_t *info)
{
char buffer[1024];
char *cwd, *dir, *oldpwd;
cwd = getcwd(buffer, 1024);
if (!cwd)
{
_puts("TODO: >>getcwd failure emsg here<<\n");
return (1);
}
if (!info->argv[1])
{
dir = get_home_dir(info);
if (!dir)
return (change_dir(info, "/"));
return (change_dir(info, dir));
}
if (_strcmp(info->argv[1], "-") == 0)
{
oldpwd = _get__env(info, "OLDPWD=");
if (!oldpwd)
return (print_cwd(cwd), 1);
if (change_dir(info, oldpwd) == -1)
return (1);
set_old_pwd(info, cwd);
set_pwd(info, oldpwd);
return (0);
}
if (change_dir(info, info->argv[1]) == -1)
return (1);
set_old_pwd(info, cwd);
set_pwd(info, getcwd(buffer, 1024));
return (0);
}


void set_pwd(info_t *info, char *buffer)
{
_setenv(info, "PWD", buffer);
}
