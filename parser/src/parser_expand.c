/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:34:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 13:44:54 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parserft.h"

static void	ft_handle_single_quote(const char *line, int *i, char **result)
{
	char	*temp;

	temp = ft_single_quotes(line, i);
	*result = ft_strjoin_free(*result, temp);
	free(temp);
}

static void	ft_toggle_double_quote(int *i, bool *in_double)
{
	*in_double = !(*in_double);
	(*i)++;
}

static void	ft_handle_variable(const char *line, t_Env *env,
				int last_exit, t_expand_state *s)
{
	if (line[s->i + 1] == '?')
		s->temp = ft_exit_code(&s->i, last_exit);
	else
		s->temp = ft_variable(line, &s->i, env);
	s->result = ft_strjoin_free(s->result, s->temp);
	free(s->temp);
}

char	*ft_expand_variables(const char *line, t_Env *env, int last_exit)
{
	t_expand_state	s;

	s.i = 0;
	s.in_single = false;
	s.in_double = false;
	s.result = ft_strdup("");
	s.temp = NULL;
	if (!line)
		return (NULL);
	while (line[s.i])
	{
		if (line[s.i] == '\'' && !s.in_double)
			ft_handle_single_quote(line, &s.i, &s.result);
		else if (line[s.i] == '\"' && !s.in_single)
			ft_toggle_double_quote(&s.i, &s.in_double);
		else if (line[s.i] == '$' && !s.in_single && line[s.i + 1])
			ft_handle_variable(line, env, last_exit, &s);
		else
			s.result = ft_append(s.result, line[s.i++]);
	}
	return (s.result);
}
