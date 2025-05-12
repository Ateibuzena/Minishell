/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_group_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:04 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/12 22:46:19 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

int	ft_special_token(const char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, "|") == 0
		&& ft_strcmp(token, "<") == 0
		&& ft_strcmp(token, ">") == 0
		&& ft_strcmp(token, "<<") == 0
		&& ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}

static void	ft_init_token(t_token *split)
{
	split->capacity = INITIAL_CAPACITY;
	split->result = malloc(split->capacity * sizeof(char *));
	if (!split->result)
	{
		perror("Tokens: Malloc Error");
		g_exit = 1;
		return ;
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

static void	ft_initialize_group(char **array, int size)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
		array[i++] = NULL;
}

char	**ft_group_tokens(char **entry, int len)
{
	t_group	group;

	group.result = ft_calloc(len, sizeof(char *));
	if (!group.result)
	{
		perror("Tokens: Malloc Error");
		ft_freedouble(entry);
		g_exit = 1;
		return (NULL);
	}
	ft_initialize_group(group.result, len);
	group.i = 0;
	group.j = 0;
	while (entry[group.i])
	{
		if (ft_is_redirect(entry[group.i]))
			group.result[group.j] = ft_process_redirect(entry, &group.i);
		else if (ft_strcmp(entry[group.i], "|") != 0)
			group.result[group.j] = ft_process_pipe(entry, &group.i);
		else
			group.result[group.j] = ft_process_command(entry, &group.i);
		group.j++;
	}
	ft_freedouble(entry);
	return (group.result);
}
