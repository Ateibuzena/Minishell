/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:57:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 21:36:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	skip_delimiters(const char *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

static char	**allocate_result(int word_count)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	return (result);
}

static void	skip_until_delim(const char *str, t_split *s, char c)
{
	while (str[s->i] && str[s->i] != c)
		(s->i)++;
}

char	**ft_split(char const *str, char c)
{
	t_split	s;

	if (!str)
		return (NULL);
	(s.i) = 0;
	(s.j) = 0;
	(s.word) = ft_word_count(str, c);
	(s.mtx) = allocate_result((s.word));
	if (!(s.mtx))
		return (NULL);
	while (str[(s.i)])
	{
		(s.i) = skip_delimiters(str, c, (s.i));
		(s.init) = (s.i);
		skip_until_delim(str, &s, c);
		if ((s.i) > (s.init))
		{
			(s.mtx)[(s.j)] = ft_strndup(str + (s.init), (s.i) - (s.init));
			if (!(s.mtx)[(s.j)])
				return (ft_freedouble((s.mtx)), NULL);
			(s.j)++;
		}
	}
	(s.mtx)[(s.j)] = NULL;
	return (s.mtx);
}
