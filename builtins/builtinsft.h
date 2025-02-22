#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../enviroment/enviromentft.h"
# include "../history/historyft.h"

/*builtins_cd.c*/
int     ft_cd(char **args);

/*builtins_clear*/
void	ft_clear(void);

/*builtins_echo.c*/
int     ft_echo(char **args);

/*builtins_env.c*/
int     ft_env(t_Env *env, char **args);

/*builtins_exit.c*/
int     ft_exit(char **args);

/*builtins_export.c*/
int     ft_export(t_Env **env, char **args);

/*builtins_pwd.c*/
int     ft_pwd(void);

/*builtins_unset.c*/
int     ft_unset(t_Env **env, char **args);

/*ft_strtok.c*/
char    *ft_strtok(char *str, const char *delim);

/*executor.c*/
int ft_execute_builtins(char **args, t_History *history, t_Env **env);
int	ft_is_builtins(char *argv);

# endif