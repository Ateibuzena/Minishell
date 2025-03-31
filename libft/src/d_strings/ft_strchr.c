/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:15:57 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 18:59:04 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strchr(const char *str, int c)
{
	t_size		i;
	t_size		len;
	char		*ptr;

	i = 0;
	c = c % 256;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (str[i] == c)
		{
			ptr = (char *)str + i;
			return (ptr);
		}
		i++;
	}
	ptr = 0;
	return (ptr);
}
