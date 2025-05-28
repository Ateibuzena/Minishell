/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanin <chanin@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:40:33 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/28 17:03:38 by chanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlen_getnextline_bonus(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_getnextline_bonus(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	join = malloc((ft_strlen_getnextline_bonus(s1)
				+ ft_strlen_getnextline_bonus(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_strchr_getnextline_bonus(const char *str, int c)
{
	if (!str || !(*str))
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

t_fdnode	*ft_newnode_getnextline_bonus(int fd)
{
	t_fdnode	*node;

	node = malloc(sizeof(t_fdnode));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->buffer = malloc(1);
	if (!node->buffer)
	{
		free(node);
		node = NULL;
		return (NULL);
	}
	node->buffer[0] = '\0';
	node->next = NULL;
	return (node);
}

char	*ft_freenode_getnextline_bonus(t_fdnode **list, int fd)
{
	t_fdnode	*actual;
	t_fdnode	*previous;

	if (!list || !*list)
		return (NULL);
	actual = *list;
	previous = NULL;
	while (actual && actual->fd != fd)
	{
		previous = actual;
		actual = actual->next;
	}
	if (!actual)
		return (NULL);
	if (previous)
		previous->next = actual->next;
	else
		*list = actual->next;
	free(actual->buffer);
	actual->buffer = NULL;
	free(actual);
	actual = NULL;
	return (NULL);
}
