/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:36:59 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 14:43:50 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERFT_H
# define PARSERFT_H

# include <fcntl.h>

//libf
# include "../libft/libft.h"
//pipex
# include "../pipex/pipexft.h"

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

/*parser_expand_utils.c*/
char	*ft_get_env(t_Env *env, const char *key);
char	*ft_single_quotes(const char *line, int *i);
char	*ft_exit_code(int *i, int last_exit);
char	*ft_variable(const char *line, int *i, t_Env *env);
char	*ft_append(char *result, char c);

/*parser_expand.c*/
char	*ft_expand_variables(const char *line, t_Env *env, int last_exit);

/*parser.c*/
int		is_quote(char c);
int		is_pipe(const char *s);
int		is_redirection(const char *s);
int		is_operator(const char *s);
char	*ft_normalize_input(const char *input);

/*parser_utils.c*/
void	ft_double_operator(const char *input, char *res, int *i, int *j);
void	ft_single_operator(const char *input, char *res, int *i, int *j);
int		validate_quotes(const char *input);
int		validate_tokens(char **tokens);
int		validate_syntax(char *input);

/*parser_quotes*/
char	*handle_no_quote(const char *input, t_quoteState *qstate);
char	*handle_single_quote(const char *input, t_quoteState *qstate);
char	*handle_double_quote(const char *input, t_quoteState *qstate);
char	*ft_handle_quotes(const char *input);

#endif