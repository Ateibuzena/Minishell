/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:02:50 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		len;
	char	*ptr;

	ptr = 0;
	len = ft_strlen(str);
	c = (unsigned char)c;
	while (len >= 0)
	{
		if (str[len] == c)
		{
			ptr = (char *)str + len;
			return (ptr);
		}
		len--;
	}
	if (c == '\0')
		ptr = (char *)str + ft_strlen(str);
	return (ptr);
}
