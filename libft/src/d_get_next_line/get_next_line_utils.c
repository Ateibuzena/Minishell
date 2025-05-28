/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanin <chanin@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:40:33 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/28 16:34:54 by chanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlen_getnextline(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_getnextline(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	n;
	size_t	len_s1;
	size_t	len_s2;

	i = -1;
	n = -1;
	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen_getnextline(s1);
	len_s2 = ft_strlen_getnextline(s2);
	join = malloc ((len_s1 + len_s2 + 1) * sizeof(char));
	if (!join || (!s1 && !s2))
		return (NULL);
	while (++i < len_s1)
		join[i] = s1[i];
	while (++n < len_s2)
		join[i++] = s2[n];
	join[i] = '\0';
	return (join);
}

char	*ft_strchr_getnextline(const char *str, int c)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	if (!str || !(*str))
		return (NULL);
	len = ft_strlen_getnextline(str);
	i = 0;
	while (i <= len)
	{
		if (str[i] && str[i] == (unsigned char)c)
		{
			ptr = (char *)str + i;
			return (ptr);
		}
		i++;
	}
	ptr = 0;
	return (ptr);
}

char	*ft_free(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (ptr);
}
