/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:41:38 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 22:50:46 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

void	ft_double_operator(const char *input, char *res, int *i, int *j)
{
	res[(*j)++] = ' ';
	res[(*j)++] = input[(*i)++];
	res[(*j)++] = input[(*i)++];
	res[(*j)++] = ' ';
}

void	ft_single_operator(const char *input, char *res, int *i, int *j)
{
	res[(*j)++] = ' ';
	res[(*j)++] = input[(*i)++];
	res[(*j)++] = ' ';
}

int	validate_quotes(const char *input)
{
	char	open;

	open = 0;
	while (*input)
	{
		if (is_quote(*input))
		{
			if (!open)
				open = *input;
			else if (*input == open)
				open = 0;
		}
		input++;
	}
	return (open == 0);
}

int	validate_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens[0])
		return (0);
	if (is_pipe(tokens[0]) || (tokens[1] == NULL && is_pipe(tokens[0])))
		return (0);
	while (tokens[i])
	{
		if (is_operator(tokens[i]))
			return (0);
		if (is_pipe(tokens[i]) && tokens[i + 1] && is_pipe(tokens[i + 1]))
			return (0);
		if (is_redirection(tokens[i]))
		{
			if (!tokens[i + 1]
				|| is_redirection(tokens[i + 1]) || is_pipe(tokens[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	validate_syntax(char *input)
{
	char	**tokens;

	if (!validate_quotes(input))
		return (0);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (0);
	if (!validate_tokens(tokens))
	{
		ft_freedouble(tokens);
		return (0);
	}
	ft_freedouble(tokens);
	return (1);
}
