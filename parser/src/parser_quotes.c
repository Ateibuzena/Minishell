/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:16:11 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/12 23:14:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parserft.h"

char	*handle_no_quote(const char *input, t_quoteState *qstate)
{
	char	c;

	c = input[qstate->i];
	if (c == '\'')
		qstate->state = SINGLE_QUOTE;
	else if (c == '\"')
		qstate->state = DOUBLE_QUOTE;
	else
		qstate->output[qstate->j++] = c;
	return (NULL);
}

char	*handle_single_quote(const char *input, t_quoteState *qstate)
{
	char	c;

	c = input[qstate->i];
	if (c == '\'')
		qstate->state = NO_QUOTE;
	else
		qstate->output[qstate->j++] = c;
	return (NULL);
}

char	*handle_double_quote(const char *input, t_quoteState *qstate)
{
	char	c;

	c = input[qstate->i];
	if (c == '\"')
		qstate->state = NO_QUOTE;
	else if (c == '\\' && qstate->i + 1 < ft_strlen(input))
		qstate->output[qstate->j++] = input[++qstate->i];
	else
		qstate->output[qstate->j++] = c;
	return (NULL);
}

static void	ft_init_state(t_quoteState *qstate)
{
	qstate->state = NO_QUOTE;
	qstate->i = 0;
	qstate->j = 0;
}

char	*ft_handle_quotes(const char *input)
{
	t_quoteState	qstate;
	size_t			len;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	ft_init_state(&qstate);
	qstate.output = malloc(len + 1);
	if (!qstate.output)
		return (NULL);
	while (qstate.i < len)
	{
		if (qstate.state == NO_QUOTE)
			handle_no_quote(input, &qstate);
		else if (qstate.state == SINGLE_QUOTE)
			handle_single_quote(input, &qstate);
		else if (qstate.state == DOUBLE_QUOTE)
			handle_double_quote(input, &qstate);
		qstate.i++;
	}
	if (qstate.state != NO_QUOTE)
		return (free(qstate.output), NULL);
	qstate.output[qstate.j] = '\0';
	return (qstate.output);
}
