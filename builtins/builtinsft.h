#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

// Definición de la estructura para almacenar variables de entorno
typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

/*builtins_cd.c*/
int     ft_cd(char **args);

/*builtins_echo.c*/
int     ft_echo(char **args);

/*builtins_env.c*/
int     ft_env(t_env *env, char **args);

/*builtins_exit.c*/
int     ft_exit(char **args);

/*builtins_export.c*/
void    ft_add_env(t_env **env, const char *key, const char *value);
int     ft_export(t_env **env, char **args);

/*builtins_pwd.c*/
int     ft_pwd(void);

/*builtins_unset.c*/
void    ft_delete_env(t_env **head, const char *key);
int     ft_unset(t_env **env, char **args);

/*ft_strtok.c*/
char    *ft_strtok(char *str, const char *delim);

/*builtins_utils.c*/
void    ft_split_env(const char *env_entry, char **key, char **value);
t_env   *ft_create_node(const char *key, const char *value);
void    ft_add_node(t_env **env_list, t_env *new_node);
t_env   *ft_copy_env(char **envp);
void    ft_free_env(t_env *env_list);

# endif