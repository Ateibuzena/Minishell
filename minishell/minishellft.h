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
//prompt
# include "../pipex/pipexft.h"
//prompt
# include "../tokens/tokensft.h"

typedef struct s_minishell
{
    char 		*prompt;         // El prompt que se muestra al usuario
    char 		*input;          // La entrada del usuario
    t_History 	*history;   // El historial de comandos
    t_Env 		*env;           // Las variables de entorno
} t_minishell;

void    ft_pipes(int argc, char **argv, char *input, t_History *history, char **env);
void    ft_tokenize(char *input, char **args);
int		ft_execute(char **args, t_History *history, t_Env **env);
void    ft_command(char *input, t_History *history, t_Env **env);

/*minishell_utils.c*/
int	ft_is_builtins(char *args);

#endif // MINISHELL_H
