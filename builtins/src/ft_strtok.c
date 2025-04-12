/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:35:42 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/12 21:37:28 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishellft.h"

static int	ft_is_delimiter(char c, const char *delimiter)
{
	while (*delimiter)
	{
		if (c == *delimiter)
			return (1);
		delimiter++;
	}
	return (0);
}

static char	*skip_delimiters(char *str, const char *delim)
{
	while (*str && ft_is_delimiter(*str, delim))
		str++;
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*token_start;

	if (str)
		next_token = str;
	if (!next_token || *next_token == '\0')
		return (NULL);
	next_token = skip_delimiters(next_token, delim);
	if (*next_token == '\0')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token;
	while (*next_token && !ft_is_delimiter(*next_token, delim))
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token_start);
}
