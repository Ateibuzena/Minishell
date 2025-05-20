/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:55:21 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 22:33:15 by azubieta         ###   ########.fr       */
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
	char	**input;
	int		len;
	int		exit;
	int		builtin;
	int		stdin_backup;
	int		stdout_backup;
}	t_context;

/*main.c*/
void	ft_initialize_shell(t_Minishell *shell, char **envp);
int		ft_read_input(t_Minishell *shell);
int		ft_process_input(t_Minishell *shell);

/*minishell_free.c*/
void	ft_cleanup_shell(t_Minishell *shell);

/*minishell_pipeline.c*/
void	ft_execute_pipeline(t_Minishell **shell, t_context *ctx);
int		ft_handle_pipeline(t_Minishell *shell);

/*minishell_handle.c*/
int		handle_heredoc(char *arg, int *i);
int		handle_input_redir(char *arg);
int		handle_append_redir(char *arg);
int		handle_output_redir(char *arg);

/*minishell_redirect.c*/
int		ft_handle_redirections(char **argv, int *stdin, int *stdout);

/*minishell_utils.c*/
int		ft_redirect_input(char *file, char *heredoc_delim);
int		ft_redirect_output(char *file);
int		ft_redirect_append(char *file);
void	ft_save_descriptors(int *saved_stdin, int *saved_stdout);
void	ft_restore_descriptors(int saved_stdin, int saved_stdout);

#endif // MINISHELL_H
