/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_group_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:04 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/01 13:30:45 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

char	**ft_split_command(const char *input)
{
	size_t		capacity;
	char		**result;
	const char	*start;
	const char	*current;
	size_t		i;

	start = input;
	current = input;
	capacity = INITIAL_CAPACITY;
	result = malloc(capacity * sizeof(char *));
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (*current)
	{
		if (*current == ' '
			|| *current == '<' || *current == '>' || *current == '|')
		{
			if (current > start)
				result[i++] = ft_process_token(start, current);
			i = ft_handle_delimiter(&current, result, i);
			start = current + 1;
		}
		if (i >= capacity)
			result = ft_resize_result(result, &capacity);
		current++;
	}
	if (current > start)
		result[i++] = ft_process_token(start, current);
	if (i >= capacity)
		result = ft_resize_result(result, &capacity);
	result[i] = NULL;
	return (result);
}

char	**ft_group_tokens(char *entry)
{
	char	**input;
	char	**result;
	size_t	i;
	size_t	j;

	input = ft_split_command(entry);
	result = malloc(MAX_TOKENS * sizeof(char *));
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
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
	ft_freedouble(input);
	return (result);
}
