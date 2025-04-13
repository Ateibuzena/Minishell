/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_group_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:04 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 21:55:37 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

static void	ft_init_token(t_token *split)
{
	split->capacity = INITIAL_CAPACITY;
	split->result = malloc(split->capacity * sizeof(char *));
	if (!split->result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	split->start = NULL;
	split->current = NULL;
	split->i = 0;
}

char	**ft_split_command(const char *input)
{
	t_token	s;

	ft_init_token(&s);
	s.start = input;
	s.current = input;
	while (*s.current)
	{
		if (*s.current == ' ' || *s.current == '<'
			|| *s.current == '>' || *s.current == '|')
		{
			if (s.current > s.start)
				s.result[s.i++] = ft_process_token(s.start, s.current);
			s.i = ft_handle_delimiter(&s.current, s.result, s.i);
			s.start = s.current + 1;
		}
		if (s.i >= s.capacity)
			s.result = ft_resize_result(s.result, &s.capacity);
		s.current++;
	}
	if (s.current > s.start)
		s.result[s.i++] = ft_process_token(s.start, s.current);
	if (s.i >= s.capacity)
		s.result = ft_resize_result(s.result, &s.capacity);
	s.result[s.i] = NULL;
	return (s.result);
}

char	**ft_group_tokens(char *entry)
{
	t_group	group;

	group.input = ft_split_command(entry);
	group.result = malloc(MAX_TOKENS * sizeof(char *));
	if (!group.result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	group.i = 0;
	group.j = 0;
	while (group.input[group.i])
	{
		if (ft_is_redirect(group.input[group.i]))
			group.result[group.j] = ft_process_redirect(group.input, &group.i);
		else if (ft_strcmp(group.input[group.i], "|") != 0)
			group.result[group.j] = ft_process_pipe(group.input, &group.i);
		else
			group.result[group.j] = ft_process_command(group.input, &group.i);
		group.j++;
	}
	group.result[group.j] = NULL;
	ft_freedouble(group.input);
	return (group.result);
}
