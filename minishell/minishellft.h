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
# include "../history/historyft.h"
//builtins
# include "../builtins/builtinsft.h"
//libf
# include "../libft/libft.h"
//prompt
# include "../prompt/promptft.h"
//pipex
# include "../pipex/pipexft.h"
//tokens
# include "../tokens/tokensft.h"

typedef struct s_minishell
{
    char 		*prompt;         // El prompt que se muestra al usuario
    char 		*input;          // La entrada del usuario
    t_History 	*history;   // El historial de comandos
    t_Env 		*env;           // Las variables de entorno
} t_minishell;

typedef enum
{
    NO_QUOTE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
} t_quoteState;

extern volatile sig_atomic_t g_in_readline;

/*minishell_utils.c*/
int    ft_handle_pipes(char *input, t_History *history, t_Env *env);
//void    ft_tokenize(char *input, char **args);
//void    ft_handle_builtin(char *input, t_History *history, t_Env **env);
char    *ft_handle_quotes(const char *input);

void    sigint_handler(int sig);
void    sigtstp_handler(int sig);
void    sigquit_handler(int sig);
void    sigterm_handler(int sig);
void    sigchld_handler(int sig);
void    sigwinch_handler(int sig);
void    setup_signals();

#endif // MINISHELL_H
