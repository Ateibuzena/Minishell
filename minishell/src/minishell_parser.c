/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:41:48 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 22:50:48 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_pipe(const char *s)
{
	return (ft_strcmp(s, "|") != 0);
}

int	is_redirection(const char *s)
{
	return (ft_strcmp(s, "<") != 0 || ft_strcmp(s, ">") != 0
		|| ft_strcmp(s, ">>") != 0 || ft_strcmp(s, "<<") != 0);
}

int	is_operator(const char *s)
{
	return (!ft_strncmp(s, "||", 2) || !ft_strncmp(s, "&&", 2));
}

char	*ft_normalize_input(const char *input)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(input) * 3 + 1);
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if ((input[i] == '<' || input[i] == '>')
				&& input[i] == input[i + 1])
				ft_double_operator(input, res, &i, &j);
			else
				ft_single_operator(input, res, &i, &j);
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}
