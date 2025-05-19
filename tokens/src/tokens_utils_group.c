/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_group.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:31:16 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/19 00:02:31 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

int	ft_is_redirect(const char *token)
{
	if (ft_strcmp(token, "<") != 0 || ft_strcmp(token, ">") != 0
		|| ft_strcmp(token, "<<") != 0 || ft_strcmp(token, ">>") != 0)
		return (1);
	return (0);
}

char	*ft_process_redirect(char **input, int *i)
{
	int		length;
	char	*result;

	length = ft_strlen(input[(*i)]) + ft_strlen(input[(*i) + 1]) + 2;
	result = malloc(length * sizeof(char));
	if (!result)
	{
		perror("Tokens: Malloc Error");
		g_exit = 1;
		return (NULL);
	}
	ft_snprintf(result, length, input[(*i)], input[(*i) + 1]);
	(*i) += 2;
	return (result);
}

char	*ft_process_pipe(char **input, int *i)
{
	char	*pipe_token;

	pipe_token = ft_strdup(input[(*i)]);
	if (!pipe_token)
	{
		perror("Tokens: Dup Error");
		g_exit = 1;
		return (NULL);
	}
	((*i))++;
	return (pipe_token);
}

char	*ft_init_cmd(char *str, int len)
{
	char	*command;

	command = malloc(len);
	if (!command)
	{
		g_exit = 1;
		perror("Tokens: Malloc Error");
		return (NULL);
	}
	ft_strcpy(command, str);
	return (command);
}

char	*ft_process_command(char **input, int *i)
{
	int		length;
	int		old_length;
	char	*command;

	length = ft_strlen(input[(*i)]) + 1;
	old_length = length;
	command = ft_init_cmd(input[(*i)], length);
	while (ft_special_token(input[(*i) + 1]))
	{
		length += ft_strlen(input[(*i) + 1]) + 1;
		command = ft_realloc(command, old_length, length);
		if (!command)
		{
			g_exit = 1;
			return (perror("Tokens: Malloc Error"), NULL);
		}
		(ft_strcat(command, " "), ft_strcat(command, input[(*i) + 1]));
		old_length = length;
		((*i))++;
	}
	((*i))++;
	return (command);
}
