/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_group.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:31:16 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 01:34:13 by azubieta         ###   ########.fr       */
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

char	*ft_process_redirect(char **input, size_t *i)
{
	size_t	length;
	char	*result;

	length = ft_strlen(input[(*i)]) + ft_strlen(input[(*i) + 1]) + 2;
	result = malloc(length * sizeof(char));
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_snprintf(result, length, input[(*i)], input[(*i) + 1]);
	(*i) += 2;
	return (result);
}

char	*ft_process_pipe(char **input, size_t *i)
{
	char	*pipe_token;

	pipe_token = ft_strdup(input[(*i)]);
	if (!pipe_token)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	((*i))++;
	return (pipe_token);
}

char	*ft_process_command(char **input, size_t *i)
{
	size_t	length;
	char	*command;

	length = ft_strlen(input[(*i)]) + 1;
	command = malloc(length * sizeof(char));
	if (!command)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(command, input[(*i)]);
	while (input[(*i) + 1] && ft_strcmp(input[(*i) + 1], "|") == 0
		&& ft_strcmp(input[(*i) + 1], "<") == 0
		&& ft_strcmp(input[(*i) + 1], ">") == 0
		&& ft_strcmp(input[(*i) + 1], ">>") == 0)
	{
		length += ft_strlen(input[(*i) + 1]) + 1;
		command = realloc(command, length);
		if (!command)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		ft_strcat(command, " ");
		ft_strcat(command, input[(*i) + 1]);
		((*i))++;
	}
	((*i))++;
	return (command);
}

void	ft_remove_pipes(char **result)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
		{
			result[j] = result[i];
			j++;
		}
		else
		{
			free(result[i]);
			result[i] = NULL;
		}
		i++;
	}
	result[j] = NULL;
}
