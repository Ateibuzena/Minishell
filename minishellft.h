#ifndef MINISHELLFT_H
# define MINISHELLFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
//history
# include <readline/readline.h>
# include <readline/history.h>
# include "history/historyft.h"
//libf
# include "libft/libft.h"
//macros
# define MAX_INPUT_SIZE 1024

// Definición de la estructura para almacenar variables de entorno
typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Funciones de manejo de tokens
char			*ft_strtok(char *str, const char *delim);

// Funciones de manejo de comandos
int				ft_echo(char **args);
int				ft_cd(char **args);
int				ft_pwd(void);
int				ft_export(t_env **env, char **args);
void			ft_delete_env(t_env **head, const char *key);
void			ft_add_env(t_env **env, const char *key, const char *value);
int				ft_unset(t_env **env, char **args);
int				ft_env(t_env *env, char **args);
int				ft_exit(char **args);
int 			ft_execute(char **args, t_History *history, t_env **env);

/*// Funciones de manejo de procesos
pid_t   create_child_process(char **args, t_env *env);
int     wait_for_process(pid_t pid);

// Funciones de manejo de redirecciones
int     handle_redirections(char **args);
int     redirect_input(char *file);
int     redirect_output(char *file);

// Funciones de manejo de señales
void    signal_handler(int sig);
void    setup_signal_handling(void);

// Funciones de parsing
char    **parse_input(char *input);
char    **split_input(char *input);
int     is_builtin(char *cmd);

// Funciones de entorno
t_env   *get_env_list(char **envp);
char    *get_env_value(t_env *env, const char *key);
void    add_env_variable(t_env **env, char *key, char *value);
void    free_env_list(t_env *env);

// Función principal para ejecutar el shell
void    minishell_loop(t_env *env);*/

#endif // MINISHELL_H
