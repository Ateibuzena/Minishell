/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_group_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:04 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 02:50:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

static int	ft_split_loop(const char *input, char ***result, int *size, int i)
{
	const char	*start;
	const char	*current;

	start = input;
	current = input;
	while (*current)
	{
		if (*current == '<' || *current == '>'
			|| *current == '|' || *current == ' ')
		{
			if (current > start)
				(*result)[i++] = ft_process_token(start, current);
			(*result)[i++] = ft_process_token(current, current + 1);
			current++;
			start = current;
		}
		else
			current++;
		if (i >= *size)
			*result = ft_resize_result(*result, size);
	}
	if (current > start)
		(*result)[i++] = ft_process_token(start, current);
	(*result)[i] = NULL;
	return (i);
}

char	**ft_split_command(const char *input)
{
	int		capacity;
	char	**result;
	int		i;

	i = 0;
	capacity = INITIAL_CAPACITY;
	result = malloc(capacity * sizeof(char *));
	if (!result)
	{
		perror("Tokens: Malloc Error");
		exit(EXIT_FAILURE);
	}
	i = ft_split_loop(input, &result, &capacity, i);
	return (result);
}

static void	ft_group_loop(char **input, char **result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (ft_is_redirect(input[i]))
			result[j] = ft_process_redirect(input, &i);
		else if (ft_strcmp(input[i], "|") != 0)
			result[j] = ft_process_pipe(input, &i);
		else
			result[j] = ft_process_command(input, &i);
		j++;
	}
	result[j] = NULL;
}

char	**ft_group_tokens(char *entry)
{
	char	**input;
	char	**result;

	input = ft_split_command(entry);
	result = malloc(MAX_TOKENS * sizeof(char *));
	if (!result)
	{
		perror("Token: Malloc Error");
		exit(EXIT_FAILURE);
	}
	ft_group_loop(input, result);
	ft_freedouble(input);
	return (result);
}
