#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../enviroment/enviromentft.h"

/*builtins_cd.c*/
int     ft_cd(char **args);

/*builtins_echo.c*/
int     ft_echo(char **args);

/*builtins_env.c*/
int     ft_env(t_env *env, char **args);

/*builtins_exit.c*/
int     ft_exit(char **args);

/*builtins_export.c*/
int     ft_export(t_env **env, char **args);

/*builtins_pwd.c*/
int     ft_pwd(void);

/*builtins_unset.c*/
int     ft_unset(t_env **env, char **args);

/*ft_strtok.c*/
char    *ft_strtok(char *str, const char *delim);

# endif