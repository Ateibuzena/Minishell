/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:55:21 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 15:52:47 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//libf
# include "../libft/libft.h"
//signals
# include "../signals/signalsft.h"
//history
# include "../history/historyft.h"
//env
# include "../enviroment/enviromentft.h"
//builtins
# include "../builtins/builtinsft.h"
//prompt
# include "../prompt/promptft.h"
//tokens
# include "../tokens/tokensft.h"
//pipex
# include "../pipex/pipexft.h"
//parser
# include "../parser/parserft.h"

typedef struct s_Minishell
{
	char		*prompt;
	char		*input;
	t_History	*history;
	t_Env		*env;
	char		*cleaned;
	char		*expanded;
	char		*normalized;
	int			status;
}	t_Minishell;

typedef struct s_context
{
	char	**argv;
	int		status;
	int		builtin;
	int		stdin_backup;
	int		stdout_backup;
}	t_context;

/*minishell_redirect.c*/
int		ft_handle_redirections(char **argv, int *stdin, int *stdout);
int		ft_handle_pipeline(t_Minishell *shell);

/*minishell_utils.c*/
int		ft_redirect_input(char *file, char *heredoc_delim);
int		ft_redirect_output(char *file);
int		ft_redirect_append(char *file);
void	ft_save_descriptors(int *saved_stdin, int *saved_stdout);
void	ft_restore_descriptors(int saved_stdin, int saved_stdout);

#endif // MINISHELL_H
