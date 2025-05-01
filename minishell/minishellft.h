/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:55:21 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 00:01:31 by azubieta         ###   ########.fr       */
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
//signals
# include "../signals/signalsft.h"

typedef struct s_minishell
{
	char		*prompt;
	char		*input;
	t_History	*history;
	t_Env		*env;
}	t_minishell;

enum e_quoteState
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

typedef struct s_quoteState
{
	enum e_quoteState state;
	size_t			i;
	size_t			j;
	char			*output;
}	t_quoteState;

typedef struct s_expand_state
{
	int		i;
	bool	in_single;
	bool	in_double;
	char	*result;
	char	*temp;
}	t_expand_state;

typedef struct s_context
{
	char	**argv;
	int		status;
	int		builtin;
	int		stdin_backup;
	int		stdout_backup;
}	t_context;

/*minishell_expand_utils.c*/
char	*ft_get_env(t_Env *env, const char *key);
char	*ft_single_quotes(const char *line, int *i);
char	*ft_exit_code(int *i, int last_exit);
char	*ft_variable(const char *line, int *i, t_Env *env);
char	*ft_append(char *result, char c);

/*minishell_expand.c*/
char	*ft_expand_variables(const char *line, t_Env *env, int last_exit);

/*minishell_parser.c*/
int		is_quote(char c);
int		is_pipe(const char *s);
int		is_redirection(const char *s);
int		is_operator(const char *s);
char	*ft_normalize_input(const char *input);

/*minishell_parser_utils.c*/
void	ft_double_operator(const char *input, char *res, int *i, int *j);
void	ft_single_operator(const char *input, char *res, int *i, int *j);
int		validate_quotes(const char *input);
int		validate_tokens(char **tokens);
int		validate_syntax(char *input);

/*minishell_quotes*/
char	*handle_no_quote(const char *input, t_quoteState *qstate);
char	*handle_single_quote(const char *input, t_quoteState *qstate);
char	*handle_double_quote(const char *input, t_quoteState *qstate);
char	*ft_handle_quotes(const char *input);

/*minishell_redirect.c*/
int		ft_handle_redirections(char **argv, int *stdin, int *stdout);
int		ft_handle_pipes(char *input, t_History *history, t_Env *env);

/*minishell_utils.c*/
int		ft_redirect_input(char *file, char *heredoc_delim);
int		ft_redirect_output(char *file);
int		ft_redirect_append(char *file);
void	ft_save_descriptors(int *saved_stdin, int *saved_stdout);
void	ft_restore_descriptors(int saved_stdin, int saved_stdout);

#endif // MINISHELL_H
