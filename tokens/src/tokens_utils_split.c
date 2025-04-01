/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:35:53 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/01 13:39:47 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

char	*ft_process_double_delimiter(const char *current)
{
	char	*token;

	token = malloc(3);
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token[0] = *current;
	token[1] = *(current + 1);
	token[2] = '\0';
	return (token);
}

char	*ft_process_token(const char *start, const char *current)
{
	size_t	length;
	char	*token;

	length = current - start;
	token = malloc(length + 1);
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(token, start, length);
	token[length] = '\0';
	return (token);
}

char	*ft_process_delimiter(const char *current)
{
	char	*token;

	token = malloc(2);
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token[0] = *current;
	token[1] = '\0';
	return (token);
}

char	**ft_resize_result(char **result, size_t *capacity)
{
	char	**new_result;
	size_t	i;

	(*capacity) *= 2;
	new_result = malloc((*capacity) * sizeof(char *));
	if (!new_result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *capacity / 2)
	{
		new_result[i] = result[i];
		i++;
	}
	free(result);
	return (new_result);
}

size_t	ft_handle_delimiter(const char **current, char **result, size_t i)
{
	if ((**current == '<' && *(*current + 1) == '<')
		|| (**current == '>' && *(*current + 1) == '>'))
	{
		result[i++] = ft_process_double_delimiter(*current);
		(*current)++;
	}
	else if (**current != ' ')
		result[i++] = ft_process_delimiter(*current);
	return (i);
}
